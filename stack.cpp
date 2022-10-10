#include "stack.h"

//-----------------------------------------------------------------------------

void stack_ctor_ext (struct Stack **stk, int capacity_ctor, const char* name, const char* filename, int line)
{
    *stk = (struct Stack*) calloc (1, sizeof (struct Stack));

    (*stk)->name_stk     = name;
    (*stk)->file_stk     = filename;
    (*stk)->line_stk     = line;

    (*stk)->canary_open  = canary_1;
    (*stk)->canary_close = canary_2;

    (*stk)->capacity_stk = capacity_ctor;
    (*stk)->size_stk     = 0;
    (*stk)->hash_code    = 0;
    (*stk)->error_codes  = ERROR_FIELD;
    (*stk)->buffer_stk   = (double*) calloc (1, capacity_ctor * sizeof (double));
    (*stk)->cur_status   = "OK";
}

//-----------------------------------------------------------------------------

void stack_dtor (struct Stack *stk)
{
    double new_hash = calculate_hash (stk);

    free (stk->buffer_stk);
    free (stk);

    verificate_stack (stk, new_hash);
}

//-----------------------------------------------------------------------------

void stack_push (struct Stack *stk, double elem)
{
    double new_hash = calculate_hash (stk);

    if((stk->size_stk) >= (stk->capacity_stk))
    {
        stack_resize (stk, stk_increase);
    }

    *((stk->buffer_stk) + (stk->size_stk)) = elem;

    (stk->size_stk)++;

    verificate_stack (stk, new_hash);
}

//-----------------------------------------------------------------------------

void stack_resize (struct Stack *stk, int opt_resize)
{
    double new_hash = calculate_hash (stk);

    if (opt_resize == stk_increase)
    {
        stk->capacity_stk*=2;

        stk->buffer_stk = (double*) realloc (stk->buffer_stk, stk->capacity_stk*sizeof (double));
    }

    else if (opt_resize == stk_decrease)
    {
        stk->capacity_stk/=2;

        stk->buffer_stk = (double*) realloc (stk->buffer_stk, stk->capacity_stk*sizeof (double));
    }

    verificate_stack (stk, new_hash);
}

//-----------------------------------------------------------------------------

double stack_pop (struct Stack *stk)
{
    double new_hash = calculate_hash (stk);

    double elem_del = stk->buffer_stk[stk->size_stk - 1];
    stk->buffer_stk[stk->size_stk - 1] = 0;

    stk->size_stk--;

    if(stk->size_stk <= stk->capacity_stk / 4)
    {
        stack_resize (stk, stk_decrease);
    }

    verificate_stack (stk, new_hash);

    return elem_del;
}

//-----------------------------------------------------------------------------

void verificate_stack (struct Stack *stk, double new_hash)   //111010111||0000000011111111
{
    if((stk->error_codes & ERROR_FIELD) != ERROR_FIELD)
    {
        stk->error_codes |= (1 << 0);
    }

    if(stk->canary_open != canary_1)
    {
        stk->error_codes |= (1 << 1);
    }

    if(stk->canary_close != canary_2)
    {
        stk->error_codes |= (1 << 2);
    }

    if(stk->buffer_stk == NULL)
    {
        stk->error_codes |= (1 << 3);
    }

    if(stk->capacity_stk < stk->size_stk)
    {
        stk->error_codes |= (1 << 4);
    }

    if(stk->capacity_stk < 0)
    {
        stk->error_codes |= (1 << 5);
    }

    if(stk->size_stk < 0)
    {
        stk->error_codes |= (1 << 6);
    }

    if(stk == NULL)
    {
        stk->error_codes |= (1 << 7);
    }

    if(stk == NULL)
    {
        stk->error_codes |= (1 << 7);
    }

    if(!(stk->hash_code - new_hash < 0.0001 && stk->hash_code - new_hash > -0.0001))
    {
        stk->error_codes |= (1 << 8);
    }

    if ((stk->error_codes | ERROR_FIELD) != ERROR_FIELD)
    {
        stk->cur_status   = "FALSE";
    }
}

//-----------------------------------------------------------------------------

double calculate_hash (struct Stack *stk)
{
    double sum = 0;

    for(int i = 0; i < stk->capacity_stk; i++)
    {
        sum += stk->buffer_stk[i];
        sum = (double)(((int) sum) % HASHPAR);
    }

    return sum;
}

//-----------------------------------------------------------------------------

void debug_stack (struct Stack *stk)
{
    handle_errors  (stk);
    stack_dump_ext (stk);
}

//-----------------------------------------------------------------------------

void handle_errors (struct Stack *stk)
{
    if((stk->error_codes | ERROR_FIELD) == ERROR_FIELD)
    {
        printf ("OK\n");
    }

    else
    {
        if(stk->error_codes & (1 << 0))
        {
            printf ("|||ATTENTION||| the integrity of error codes violated!\n\n");
        }

        if(stk->error_codes & (1 << 1))
        {
            printf ("ERROR - the integrity of first canary is broken\n");
        }

        if(stk->error_codes & (1 << 2))
        {
            printf ("ERROR - the integrity of second canary is broken\n");
        }

        if(stk->error_codes & (1 << 3))
        {
            printf ("ERROR - incorrect memory allocation for stack's data (NULL-pointer)\n");
        }

        if(stk->error_codes & (1 << 4))
        {
            printf ("ERROR - stack overflow\n");
        }

        if(stk->error_codes & (1 << 5))
        {
            printf ("ERROR - incorrect capacity value (below zero)\n");
        }

        if(stk->error_codes & (1 << 6))
        {
            printf ("ERROR - incorrect size value (below zero)\n");;
        }

        if(stk->error_codes & (1 << 7))
        {
            printf ("ERROR - incorrect memory allocation for stack (NULL-pointer\n");
        }

        if(stk->error_codes & (1 << 8))
        {
            printf ("ERROR -  invalid hash\n");
        }
    }
}

//-----------------------------------------------------------------------------

void stack_dump_ext (struct Stack *stk)
{
    printf ("%s[%p](%s) at %s, LINE - %d \n"
            "{                           \n"
            "    canary_open  = %x       \n"
            "    canary_close = %x       \n"
            "    size_stk     = %d       \n"
            "    capacity_stk = %d       \n"
            "                            \n"
            "    buffer_stk[%p]          \n"
            "    {                       \n",
            stk->name_stk + 1, stk, stk->cur_status, stk->file_stk, stk->line_stk,
            stk->canary_open,
            stk->canary_close,
            stk->size_stk,
            stk->capacity_stk,
            stk->buffer_stk);

    for(int pos = 0; pos < stk->capacity_stk; pos++)
    {
        printf (

        "          *[%d] = %lg\n",
        /*cur_status_elem*/ pos, stk->buffer_stk[pos]);
    }

    printf ("    }                  \n"
            "}                      \n");
}

//-----------------------------------------------------------------------------
