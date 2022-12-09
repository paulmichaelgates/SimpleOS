# SimpleOS

SimpleOS is a Texas Instruments MSP430 family operating system created for learning and expiremental purposes.
Initial development being done on MSP430FR2355, but the hope is to expand to other MCUs over time.

# Project Structure

Development of the project is not IDE dependent, that being said there are two recomended options:

1. Code Composer Studio (CCS)

    Texas Instrument supported IDE that is basically Eclipse, but with a lot more relevant tools for
    developing on TI hardware. The type of project will be 'Makefile Expiremental' since that is the
    the project is built using make.

2. Standalone MSP430-GCC

    Utilizes the MSP430-GCC tool chain to accomplish tasks such as flashing device, debuging, building
    an image, etc.

    .vscode and .code-workspace files configured for running these tasks given that the proper tools
    are setup in /tools (see info below about what needs to go in these directories)
    
    go [here](https://code.visualstudio.com/docs/editor/tasks) for info about vscode tasks


refer to MSP430 GCC User's Guide for more information on using CCS versus standalone MSP430-GCC, for new embedded
software developers, I recommend using CCS since it will provide a nice GUI for tools used in the project.

See [TI MSP440 GCC Tool Chain User's Guide](https://www.ti.com/lit/ug/slau646f/slau646f.pdf?ts=1670125317847&ref_url=https%253A%252F%252Fwww.google.com%252F) for more details


# /tools Directory

The project uses libraries provided by TI, these are all available via an up to date msp43-gcc installation
which can be found [here](https://www.ti.com/tool/MSP430-GCC-OPENSOURCE)

after install copy folder called 'msp430-gcc' under the tools directory in order to use .vscode created tools.


# Texas Instruments READ ME info

For MSP430 CPU generation 1 and 2, we recommend to add the following additional compiler flags:
    -mlarge -mcode-region=either -mdata-region=lower
To check if your device is CPU generation 1 or 2, open the devices.csv file (${INSTALL_DIR}/include) and look up the column CPU_TYPE.
For MSP430 CPU generation 0, those flags should not be added to the Makefile.
