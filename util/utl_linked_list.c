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

list_t * find(list_t * head, int key) {

   list_t* current = head;

   if(head == NULL) {
      return NULL;
   }

   while(current->key != key) {
	
      if(current->next == NULL) {
         return NULL;
      } else {
         current = current->next;
      }
   }      
	
   return current;
}

list_t * delete(list_t * head, int key) {

    list_t* current = head;
    list_t* previous = NULL;
	
   if(head == NULL) {
      return NULL;
   }

   while(current->key != key) {

      if(current->next == NULL) {
         return NULL;
      } else {
         previous = current;
         current = current->next;
      }
   }

   if(current == head) {
      head = head->next;
   } else {
      previous->next = current->next;
   }    
	
   return current;
}
