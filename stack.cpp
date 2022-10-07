
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>

//-----------------------------------------------------------------------------

//#define DUMP(varname) #varname

//-----------------------------------------------------------------------------

#define POISON 50161703917

//-----------------------------------------------------------------------------

#define stk_increase 1
#define stk_decrease 0
#define SUCCESS 0

//-----------------------------------------------------------------------------

int stack_ctor   (struct Stack *stk, int capacity_ctor);
int stack_dtor   (struct Stack *stk);

double stack_pop (struct Stack *stk);
int stack_push   (struct Stack *stk, double elem);
int stack_resize (struct Stack *stk, int opt_resize);

int stack_dmp    (struct Stack *stk);

//-----------------------------------------------------------------------------

struct Stack
{
    char   *name_stk;
    double *buffer_stk;

    int     capacity_stk;
    int     size_stk;

    unsigned int mis_code;
};

//-----------------------------------------------------------------------------

int main ()
{
    setlocale (LC_ALL, "Russian");

    struct Stack stk1 = {0};

    stack_ctor (&stk1, 10);// == 0 || Error ("");

    for(int i = 1000; i < 1056; i++)
    {
        stack_push (&stk1, i);
    }

    stack_pop  (&stk1);

    stack_dmp  (&stk1);

    stack_dtor (&stk1);

    return 0;
}

//-----------------------------------------------------------------------------

int stack_ctor (struct Stack *stk, int capacity_ctor)
{
    stk->capacity_stk = capacity_ctor;
    stk->size_stk = 0;
    stk->mis_code = 0;

    stk->buffer_stk = (double*) calloc (1, capacity_ctor * sizeof (double));

    if(stk->buffer_stk == NULL)
    {
        stk->mis_code |= 1;    //incorrect memory allocation
    }

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_dtor (struct Stack *stk)
{
    free (stk);

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_push (struct Stack *stk, double elem)
{
    if((stk->size_stk) == (stk->capacity_stk))
    {
        stack_resize (stk, stk_increase);
    }

    *((stk->buffer_stk) + (stk->size_stk)) = elem;

    (stk->size_stk)++;

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_resize (struct Stack *stk, int opt_resize)
{
    if (opt_resize == stk_increase)
    {
        stk->capacity_stk*=2;

        stk->buffer_stk = (double*) realloc (stk->buffer_stk, stk->capacity_stk*sizeof (double));

        if(stk->buffer_stk == NULL)unidentified element found
        {
            stk->mis_code |= 4;    //incorrect memory reallocation
        }
    }

    else if (opt_resize == stk_decrease)
    {
        stk->capacity_stk/=2;

        stk->buffer_stk = (double*) realloc (stk->buffer_stk, stk->capacity_stk*sizeof (double));

        if(stk->buffer_stk == NULL)
        {
            stk->mis_code |= 4;    //incorrect memory reallocation
        }

        if(stk->capacity_stk < stk->size_stk)
        {
            stk->mis_code |= 8;    //stack overflow
        }
    }

    else
    {
        stk->mis_code |= 2;    //incorrect recize parameters
    }
}

//-----------------------------------------------------------------------------

double stack_pop (struct Stack *stk)
{
    double elem_del = stk->buffer_stk[stk->size_stk];

    if(elem_del == POISON)
    {
        stk->mis_code |= 8;    //unidentified element found
    }

    stk->size_stk--;

    if(stk->size_stk <= stk->capacity_stk / 4)
    {
        stack_resize (stk, stk_decrease);
    }

    return elem_del;
}

//-----------------------------------------------------------------------------

int stack_dmp    (struct Stack *stk)
{
    printf ("%s[%p](ok) at %s    \n"
            "{                      \n"
            "    size_stk     = %d  \n"
            "    capacity_stk = %d  \n"
            "                       \n"
            "    buffer_stk[%p]       \n"
            "    {                  \n",
            stk->name_stk,
            stk,
            /*stk->cur_status_stk,*/
            __FILE__,
            stk->capacity_stk,
            stk->size_stk,
            stk->buffer_stk);

    for(int pos = 0; pos < stk->capacity_stk; pos++)
    {
        printf (

        "          *[%d] = %lg\n",
        /*cur_status_elem*/ pos, stk->buffer_stk[pos]);
    }

    printf ("    }                  \n"
            "}                      \n");

    return SUCCESS;
}

//-----------------------------------------------------------------------------
