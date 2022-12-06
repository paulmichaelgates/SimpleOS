/*

utl_types.h

*/
#ifndef UTL_TYPES_H
#define UTL_TYPES_H

/* project err */
typedef enum 
{
    NO_ERR,
    INVALID_PRMT

}err_t;


/* linked list */
typedef struct 
{
    list_t * next;

}list_t;


#endif /* UTL_TYPES_H */