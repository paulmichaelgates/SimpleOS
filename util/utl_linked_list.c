#include "utl_simple.h"

list_t *current = NULL;

void utl_list_insert_new_link(list_t * head, list_t * node) 
{
   node->next = head;
   head = node;
}

list_t * deleteFirst(list_t * head) {

   list_t *tempLink = head;
   head = head->next;

   return tempLink;
}

//is list empty
boolean isEmpty(list_t * head) {
   return head == NULL;
}

int length(list_t * head) {
   int length = 0;
   list_t *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

//find a link with given key
list_t * find(list_t * head, int key) {

   //start from the first link
   list_t* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if data found, return the current Link
   return current;
}

//delete a link with given key
list_t * delete(list_t * head, int key) {

    //start from the first link
    list_t* current = head;
    list_t* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->key != key) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      previous->next = current->next;
   }    
	
   return current;
}
