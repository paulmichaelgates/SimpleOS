/*

utl_simple.h

*/
#ifndef UTL_SIMPLE_H
#define UTL_SIMPLE_H

/*---------------------------------------
 Literal constants
----------------------------------------*/
#define NULL 0

/*---------------------------------------
 Project Wide Data Types
----------------------------------------*/

/* uint 8 */
typedef char uint8;

/* uint 16 */
typedef unsigned short uint16;

/* boolean */
typedef unsigned short boolean;

/* project err */
typedef enum 
{
    NO_ERR,
    INVALID_PRMT

}err_t;


/* linked list */
typedef struct list_struc
{
    void * data;
    int key;
    struct list_struc * next;

}list_t;

/*---------------------------------------
 Procedures for interacting with types
----------------------------------------*/

                    /* util_linked_list */
void utl_list_insert_new_link(list_t * head, list_t * node);

#endif /* UTL_SIMPLE */