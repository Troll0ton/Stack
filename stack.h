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

#define canary_1 0xBADDED
#define canary_2 0xDEDBAD

//-----------------------------------------------------------------------------

#define NUM_OF_MIS 9

//-----------------------------------------------------------------------------

#define ERROR_FIELD 30867456 //111010111||0000000000000000

//-----------------------------------------------------------------------------

#define stack_ctor(X, Y) stack_ctor_ext (X, Y, #X, __FILE__,  __LINE__)
#define stack_dump()     stack_dump_ext (X,        __FILE__,  __LINE__)

//-----------------------------------------------------------------------------

#define stk_increase 1
#define stk_decrease 0

//-----------------------------------------------------------------------------

struct Stack
{
    unsigned int   canary_open;

    const char    *name_stk;
    const char    *file_stk;
    int            line_stk;
    double        *buffer_stk;

    int            capacity_stk;
    int            size_stk;

    long long int  error_codes;

    char          *cur_status;
    unsigned int   hash_code;

    unsigned int   canary_close;
};

//-----------------------------------------------------------------------------

void    stack_ctor_ext   (struct Stack **stk, int capacity_ctor, const char* name, const char* filename, int line);
void    stack_dtor       (struct Stack *stk);
double  stack_pop        (struct Stack *stk);
void    stack_push       (struct Stack *stk, double elem);
void    stack_resize     (struct Stack *stk, int opt_resize);
void    stack_dump_ext   (struct Stack *stk);
void    verificate_stack (struct Stack *stk, unsigned int new_hash);
void    handle_errors    (struct Stack *stk);
void    debug_stack      (struct Stack *stk);
void    make_statements  (struct Stack *stk, unsigned int new_hash);
unsigned int  calculate_hash   (struct Stack *stk);

//-----------------------------------------------------------------------------

#endif //STACK_H
