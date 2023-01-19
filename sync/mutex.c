/*
mutex.c
*/

#include "utl_simple.h"
#include "mutex.h"
#include "task_pub.h"

/* 
local macors
*/
#define assign_owner( id, tsk ) ( s_mutex_lut[ ( id ) ].owner = ( tsk ) )

#define has_owner( id ) ( s_mutex_lut[ ( id ) ].owner != NULL )
/* 
local memory constants
*/
#define MAX_MTX_CNT 0x10000

/* 
 local module types
*/
typedef struct
{
    tcb_t *     owner;
    mutex_def_t def;

}mutex_lut_t;

typedef struct
{
    uint16_t mutex_cnt;
}mutex_ctrl_t;
mutex_ctrl_t mutex_ctrl;
/* 
 local module variables
    this must be initialized on boot
    up by the project using this kernel
*/
mutex_lut_t * s_mutex_lut;

/* 
 local module procedures
*/
static boolean check_valid_mutex
    (
        mutex_id_t id
    );


static err_t create_mutex
    (
    mutex_def_t * prj_def
    );

err_t mutex_init_module
    (
    mutex_def_t * prj_def,
    uint32_t      size
    )
{
    /* local variables */
    uint32_t     count;
    mutex_ctrl_t mutex_ctrl;
    mutex_lut_t  table[ count ];

    /* input validation */
    count = ( size / sizeof( mutex_def_t ) );
    if( count > MAX_MTX_CNT )
        {
        return( INVALID_PRMT );
        }

    /* intialize the look up table */
    s_mutex_lut = &table;

    /* initialize control structure */
    mutex_ctrl.mutex_cnt =  ( uint16_t )count;

    create_mutex( prj_def );
}

/*
    mutex_reserve()

    called by a task attempting to reserve
    a mutex (blocking call)
*/
err_t mutex_reserve
    (
    mutex_id_t m_id
    )
{

/* local variables */
tcb_t * current_task;

/*  check that the id is in the list
     of known mutex
*/
if( has_owner( m_id ) )
    {
    /* TODO handle mutex has owner */
    }

/* since the mutex is not owned
    the current task may have it */
assign_owner( m_id, TSK_get_current() );

return( NO_ERR );

}

static err_t create_mutex
    (
    mutex_def_t * prj_def
    )
{
/* local variables */
uint16_t index;
uint16_t tmp_id;

/* iterate over each definition 
    and add the appropriate mtx
    defininitions
*/
for( index = 0; index < cnt_of_arr( prj_def ); index++ )
    {
        /* validate that this id conforms
            to the correct format
        */
        tmp_id = prj_def[ index ].id;
        if( tmp_id < cnt_of_arr( prj_def ) )
            {
            s_mutex_lut = NULL;
            return( INVALID_PRMT );
            }

        /* set up the mutex look up table */
        s_mutex_lut[ tmp_id ].def   = prj_def[ index ];
        s_mutex_lut[ tmp_id ].owner = NULL; 
    }
}