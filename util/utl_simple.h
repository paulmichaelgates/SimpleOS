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

/* boolean */
typedef short unsigned boolean;

/* uint16 */
typedef short unsigned uint16_t;

/* uint8 */
typedef unsigned char uint8_t;


/* uint32 */
typedef unsigned int uint32_t;

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