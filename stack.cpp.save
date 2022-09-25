#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------

#define stk_increase 1
#define stk_decrease 0
#define SUCCESS 0

//-----------------------------------------------------------------------------

int stack_Ctor   (struct Stack *stk, int capacity_ctor);
int stack_Dtor   (struct Stack *stk);

int stack_pop    (struct Stack *stk);
int stack_push   (struct Stack *stk, double elem);
int stack_resize (struct Stack *stk, int opt_resize);

//-----------------------------------------------------------------------------

struct Stack
{
    double *data_stk;

    int capacity_stk;
    int size_stk;
};

//-----------------------------------------------------------------------------

int main ()
{
    struct Stack stk1 = {NULL, 0, 0};
    stack_Ctor (&stk1, 10);// == 0 || Error ("");

    stack_push (&stk1, 100);
    stack_push (&stk1, 101);
    stack_push (&stk1, 102);
    stack_push (&stk1, 103);

    stack_pop (&stk1);

    stack_Dtor (&stk1);

    return 0;
}

//-----------------------------------------------------------------------------

int stack_Ctor (struct Stack *stk, int capacity_ctor)
{
    (stk -> capacity_stk) = capacity_ctor;
    (stk -> size_stk) = 0;

    (stk -> data_stk) = (double*) calloc (capacity_ctor, sizeof (double));

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_Dtor (struct Stack *stk)
{
    free (stk);

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_push (struct Stack *stk, double elem)
{
    if((stk -> size_stk) >= (stk -> capacity_stk))
    {
        stack_resize (stk, stk_increase);
    }

    *((stk -> data_stk) + (stk -> size_stk)) = elem;

    (stk -> size_stk)++;

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_resize (struct Stack *stk, int opt_resize)
{
    if (opt_resize == stk_increase)
    {
        (stk -> capacity_stk)*=2;

        (stk -> data_stk) = (double*) realloc ( (stk -> data_stk), (stk -> capacity_stk)*sizeof (double));
    }

    if (opt_resize == stk_decrease)
    {
        (stk -> capacity_stk)/=2;

        (stk -> data_stk) = (double*) realloc ( (stk -> data_stk), (stk -> capacity_stk)*sizeof (double));
    }

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_pop (struct Stack *stk)
{
    *((stk -> data_stk) + (stk -> size_stk)) = 0;

    (stk -> size_stk)--;

    if((stk -> size_stk) <= ((stk -> capacity_stk) / 4))
    {
        stack_resize (stk, stk_decrease);
    }

    return SUCCESS;
}

//-----------------------------------------------------------------------------
