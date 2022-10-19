//! @file stack.h

#ifndef   STACK_H
#define   STACK_H

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <limits.h>

//-----------------------------------------------------------------------------

#define  LEFT_CANARY
#define  RIGHT_CANARY

#define canary_1 0xBADDED
#define canary_2 0xDEDBAD

//-----------------------------------------------------------------------------

#define NUM_OF_MIS 9

//-----------------------------------------------------------------------------

// 0x
#define ERROR_FIELD 30867456 //111010111||0000000000000000

//-----------------------------------------------------------------------------

// stack, capacity??

#define stack_ctor(X, Y) stack_ctor_ext (X, Y, #X, __FILE__,  __LINE__)
#define stack_dump()     stack_dump_ext (X,        __FILE__,  __LINE__)

//-----------------------------------------------------------------------------

#define stk_increase 1
#define stk_decrease 0

struct StackInfo
{

};

//-----------------------------------------------------------------------------


// struct Stack;
// int STACK_SIZE = 64;


struct Stack
{
    unsigned int   canary_open;
    const char    *name_stk; // StackInfo
    const char    *file_stk;
    int            line_stk;
    double        *buffer_stk;
    int            capacity_stk;
    int            size_stk;
    long long int  error_codes;
    char          *cur_status;
    unsigned int   hash_code; // hash
    unsigned int   canary_close;
};

//-----------------------------------------------------------------------------

struct Error_info
{
    unsigned int error_code;
    char *error_output;
};

//-----------------------------------------------------------------------------

const struct Error_info error_arr[]
{
    {(1 << 0),  "|||ATTENTION||| the integrity of error codes violated!           \n\n"},
    {(1 << 1),  "ERROR - the integrity of first canary is broken                    \n"},
    {(1 << 2),  "ERROR - the integrity of second canary is broken                   \n"},
    {(1 << 3),  "ERROR - incorrect memory allocation for stack's data (NULL-pointer)\n"},
    {(1 << 4),  "ERROR - stack overflow                                             \n"},
    {(1 << 5),  "ERROR - incorrect capacity value (below zero)                      \n"},
    {(1 << 6),  "ERROR - incorrect size value (below zero)                          \n"},
    {(1 << 7),  "ERROR - incorrect memory allocation for stack (NULL-pointer)       \n"},
    {(1 << 8),  "ERROR - data integrity breach (invalid hash)                       \n"},
};


//-----------------------------------------------------------------------------
// ??
enum ERROR_CODES
{
    ERR_FIELD  = (1 << 0),
    ERR_CAN_1  = (1 << 1),
    ERR_CAN_2  = (1 << 2),
    ERR_MEMBUF = (1 << 3),
    ERR_OVERF  = (1 << 4),
    ERR_CAP    = (1 << 5),
    ERR_SIZE   = (1 << 6),
    ERR_MEMSTK = (1 << 7),
    ERR_HASH   = (1 << 8)
};

//-----------------------------------------------------------------------------

// ??

void          stack_ctor_ext   (struct Stack **stk, int         capacity_ctor,
                                const char* name,   const char* filename,
                                int line);
void          stack_dtor       (struct Stack *stk);
double        stack_pop        (struct Stack *stk);
void          stack_push       (struct Stack *stk, double elem);
void          stack_resize     (struct Stack *stk, int opt_resize);
void          stack_dump_ext   (struct Stack *stk);
void          verificate_stack (struct Stack *stk, unsigned int new_hash);
void          handle_errors    (struct Stack *stk);
void          debug_stack      (struct Stack *stk);
void          check_errors     (struct Stack *stk, unsigned int new_hash);
unsigned int  calculate_hash   (struct Stack *stk);
double       *recalloc         (double *buffer, int capacity, int size);

//-----------------------------------------------------------------------------

#endif //STACK_H
