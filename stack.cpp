#include "stack.h"

//-----------------------------------------------------------------------------

void stack_ctor_ext (struct Stack **stk, int capacity_ctor, const char* name, const char* file_name, int line)
{
    *stk = (struct Stack*) calloc (1, sizeof (struct Stack));

    (*stk)->name_stk     = name;
    (*stk)->file_stk     = file_name;
    (*stk)->line_stk     = line;
    (*stk)->canary_open  = canary_1;
    (*stk)->canary_close = canary_2;
    (*stk)->capacity_stk = capacity_ctor;
    (*stk)->size_stk     = 0;
    (*stk)->error_codes  = ERROR_FIELD;

    if(capacity_ctor > 0)
    {
        (*stk)->buffer_stk = (double*) calloc (1, capacity_ctor * sizeof (double));
    }

    (*stk)->cur_status = "OK";
    (*stk)->hash_code  = calculate_hash (*stk);
}

//-----------------------------------------------------------------------------

void stack_dtor (struct Stack *stk)
{
    unsigned int new_hash = calculate_hash (stk);

    verificate_stack (stk, new_hash);

    free (stk->buffer_stk);
    free (stk);

    stk->hash_code = calculate_hash (stk);
}

//-----------------------------------------------------------------------------

void stack_push (struct Stack *stk, double elem)
{
    unsigned int new_hash = calculate_hash (stk);

    verificate_stack (stk, new_hash);

    if((stk->size_stk + 1) > (stk->capacity_stk))
    {
        stack_resize (stk, stk_increase);
    }

    *((stk->buffer_stk) + (stk->size_stk)) = elem;

    (stk->size_stk)++;

    stk->hash_code = calculate_hash (stk);
}

//-----------------------------------------------------------------------------

void stack_resize (struct Stack *stk, int opt_resize)
{
    if (opt_resize == stk_increase)
    {
        if(stk->capacity_stk == 0)
        {
            stk->capacity_stk = 2;
        }

        stk->capacity_stk*=2;

        stk->buffer_stk = (double*) recalloc (stk->buffer_stk, stk->capacity_stk, stk->size_stk);
    }

    else if (opt_resize == stk_decrease)
    {
        stk->capacity_stk/=2;

        stk->buffer_stk = (double*) recalloc (stk->buffer_stk, stk->capacity_stk, stk->size_stk);
    }

    stk->hash_code = calculate_hash (stk);
}

//-----------------------------------------------------------------------------

double stack_pop (struct Stack *stk)
{
    unsigned int new_hash = calculate_hash (stk);

    verificate_stack (stk, new_hash);

    double elem_del = stk->buffer_stk[stk->size_stk - 1];
    stk->buffer_stk[stk->size_stk - 1] = 0;

    stk->size_stk--;

    if(stk->size_stk <= stk->capacity_stk / 4)
    {
        stack_resize (stk, stk_decrease);
    }

    stk->hash_code = calculate_hash (stk);

    return elem_del;
}

//-----------------------------------------------------------------------------

void verificate_stack (struct Stack *stk, unsigned int new_hash)   //111010111||0000000011111111
{
    check_errors (stk, new_hash);

    if ((stk->error_codes | ERROR_FIELD) != ERROR_FIELD)
    {
        stk->cur_status   = "ERROR";
    }
}

//-----------------------------------------------------------------------------

unsigned int calculate_hash (struct Stack *stk)
{
    unsigned int sum      = 0;
    unsigned int hash_par = 17;

    for(int i = 0; i < stk->capacity_stk; i++)
    {
        sum += (int)(stk->buffer_stk[i]*100*hash_par);
        sum %= UINT_MAX;
        hash_par *= 17;
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
        for(int i = 0; i < NUM_OF_MIS; i++)
        {
            if(stk->error_codes & error_arr[i].error_code)
            {
                printf ("%d %s\n", error_arr[i].error_code, error_arr[i].error_output);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void stack_dump_ext (struct Stack *stk)
{
    FILE *log_file = fopen ("log.txt", "w+");

    fprintf (log_file,
            "%s[%p](%s) at %s, LINE - %d \n"
            "{                           \n"
            "    canary_open  = %x       \n"
            "    canary_close = %x       \n"
            "    hash         = %x       \n"
            "    size_stk     = %d       \n"
            "    capacity_stk = %d       \n"
            "                            \n"
            "    buffer_stk[%p]          \n"
            "    {                       \n",

            stk->name_stk + 1, stk, stk->cur_status, stk->file_stk, stk->line_stk,
            stk->canary_open,
            stk->canary_close,
            stk->hash_code,
            stk->size_stk,
            stk->capacity_stk,
            stk->buffer_stk);

    for(int pos = 0; pos < stk->capacity_stk; pos++)
    {
        fprintf (log_file,
            "          [%d] = %lg        \n",
                    pos,   stk->buffer_stk[pos]);
    }

    fprintf (log_file,
            "    }                       \n"
            "}                           \n");

    fclose (log_file);
}

//-----------------------------------------------------------------------------

void check_errors (struct Stack *stk, unsigned int new_hash)
{
    if((stk->error_codes & ERROR_FIELD) != ERROR_FIELD) stk->error_codes|=ERR_FIELD;
    if(stk->canary_open != canary_1)                    stk->error_codes|=ERR_CAN_1;
    if(stk->canary_close != canary_2)                   stk->error_codes|=ERR_CAN_2;
    if(stk->buffer_stk == NULL)                         stk->error_codes|=ERR_MEMBUF;
    if(stk->capacity_stk < stk->size_stk)               stk->error_codes|=ERR_OVERF;
    if(stk->capacity_stk < 0)                           stk->error_codes|=ERR_CAP;
    if(stk->size_stk < 0)                               stk->error_codes|=ERR_SIZE;
    if(stk == NULL)                                     stk->error_codes|=ERR_MEMSTK;
    if(stk->hash_code != new_hash)                      stk->error_codes|=ERR_HASH;
}

//-----------------------------------------------------------------------------

double *recalloc (double *buffer, int capacity, int size)
{
    buffer = (double*) realloc (buffer, capacity*sizeof (double));

    for(int pos = size; pos < capacity; pos++)
    {
        buffer[pos] = 0;
    }

    return buffer;
}

//-----------------------------------------------------------------------------


