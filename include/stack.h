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
#include <stdint.h>

//-----------------------------------------------------------------------------

#define LEFT_CANARY  0xBADDED
#define RIGHT_CANARY 0xDEDBAD

//-----------------------------------------------------------------------------

#define NUM_OF_MIS 8

//-----------------------------------------------------------------------------

#define ERROR_FIELD 0

//-----------------------------------------------------------------------------

#define stack_ctor(Stk, capacity) stack_ctor_ (Stk, capacity, #Stk, __FILE__,  __LINE__)
#define stack_dump(Stk)           stack_dump_ (Stk,                 __FILE__,  __LINE__)

//-----------------------------------------------------------------------------

#define Stk_INCREASE 1
#define Stk_DECREASE 0

//-----------------------------------------------------------------------------

enum Hsh_pars
{
    HASH_CONST = 17,
    HASH_BASE  = 100,
};

//-----------------------------------------------------------------------------

typedef struct StackInfo
{
    const char *name;
    const char *file;
    int         line;
    int         error_codes;
    char       *cur_status;
} StackInfo;

//-----------------------------------------------------------------------------

typedef struct Stack
{
    int       canary_left;
    StackInfo Stack_info;
    double   *buffer_stk;
    int       capacity_Stk;
    int       size_Stk;
    int       hash;
    int       canary_right;
} Stack;

//-----------------------------------------------------------------------------

typedef struct Error_info
{
    int     error_code;
    char   *error_output;
} Error_info;

//-----------------------------------------------------------------------------

enum ERROR_CODES
{
    ERR_CAN_1  = (1 << 1),
    ERR_CAN_2  = (1 << 2),
    ERR_MEMBUF = (1 << 3),
    ERR_OVERF  = (1 << 4),
    ERR_CAP    = (1 << 5),
    ERR_SIZE   = (1 << 6),
    ERR_MEMStk = (1 << 7),
    ERR_HASH   = (1 << 8)
};

//-----------------------------------------------------------------------------

const struct Error_info error_arr[]
{
    {ERR_CAN_1,  "ERROR - the integrity of first canary is broken                    \n"},
    {ERR_CAN_2,  "ERROR - the integrity of second canary is broken                   \n"},
    {ERR_MEMBUF, "ERROR - incorrect memory allocation for stack's data (NULL-pointer)\n"},
    {ERR_OVERF,  "ERROR - stack overflow                                             \n"},
    {ERR_CAP,    "ERROR - incorrect capacity value (below zero)                      \n"},
    {ERR_SIZE,   "ERROR - incorrect size value (below zero)                          \n"},
    {ERR_MEMStk, "ERROR - incorrect memory allocation for stack (NULL-pointer)       \n"},
    {ERR_HASH,   "ERROR - data integrity breach (invalid hash)                       \n"},
};

//-----------------------------------------------------------------------------

int     stack_ctor_      (Stack *Stk,            int capacity_ctor, const char* stk_name,
                          const char* file_name, int stk_line                            );
void    stack_dtor       (Stack *Stk);
double  stack_pop        (Stack *Stk);
void    stack_push       (Stack *Stk, double elem);
void    stack_resize     (Stack *Stk, int opt_resize);
void    stack_dump_      (Stack *Stk);
void    verificate_stack (Stack *Stk, int new_hash);
void    handle_errors    (Stack *Stk);
void    debug_stack      (Stack *Stk);
void    check_errors     (Stack *Stk, int new_hash);
int     calculate_hash   (Stack *Stk);
void   *recalloc         (void *buffer, int capacity, int size, int size_of_type);

//-----------------------------------------------------------------------------

#endif //STACK_H
