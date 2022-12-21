from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys
import os
import time
import appscript

#--------------------------------------------------------------------------
#
#
#   debug_gui.py
#
#   Description
#       easy to use gui to automate some basic development tools
#   
#   Note
#       currently only works for macos
#
#---------------------------------------------------------------------------

""" defines the main window """
class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self._initComponents()
        self._initUI()

    def _initComponents(self):
        self.debug = Debug()

    def _initUI(self):
        self._createDebugButton()
        self._createMessageLabel()

    def _createDebugButton(self):
        self.runButton = QtWidgets.QPushButton(self)
        self.runButton .setGeometry(20, 100, 200, 100)
        self._idleDebugButton()

    def _idleDebugButton(self):
        self.runButton .setText("Run Config")
        self.runButton .clicked.connect(self._startDebugWrapper)        

    def _createMessageLabel(self):
        self.msgLabel = QtWidgets.QLabel(self)
        self.msgLabel.setGeometry(20, 20, 200, 50)
        self._idleMessagLabel()

    def _idleMessagLabel(self):
        self.msgLabel.setText("No active session")

    def _startDebugWrapper(self):
    
        if(self.debug.startDebug() == 0):
            self.runButton.setText("Stop session")

            # reset button event
            self.runButton.disconnect()
            self.runButton.clicked.connect(lambda: self._stopDebugWrapper())

            self.msgLabel.setText("Debug session active...")
        else:
            self.msgLabel.setText("An error occured, could not start debug session")
    
    def _stopDebugWrapper(self):
        self.msgLabel.setText("terminating debug session...")
        self.debug.stopDebug()
        time.sleep(1)
        self._idleMessagLabel()

        self._idleDebugButton()

class Debug():

    def __init__(self):
        self._initComponents()

    def _initComponents(self):
        self.debugSessionApps = []

    def startDebug(self):
        print("starting debug session....")
        
        cwd = os.getcwd()

        # start gcc
        gccTerminal = appscript.app("Terminal")        
        gccTerminal.do_script("cd "  + cwd + " && make debug")

        # start the debug server
        debugServer = appscript.app("Terminal")
        debugServer.do_script("cd "  + cwd + " && cd tools/msp430-gcc && ./bin/gdb_agent_console msp430.dat")

        self.debugSessionApps.append(gccTerminal)
        self.debugSessionApps.append(debugServer)

        # return success
        return 0

    def stopDebug(self):
        self.debugSessionApps = [] # clear all active debug applications

""" Start the application """
def start():
    app = QApplication(sys.argv)
    win = MainWindow()
    win.setGeometry(100, 100, 240, 300)
    win.setWindowTitle("SimpleOS Debugger Tool")

    win.show()

    sys.exit(app.exec_())

start()