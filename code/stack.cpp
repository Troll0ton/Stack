#include "../include/stack.h"

//-----------------------------------------------------------------------------

int stack_ctor_ (struct Stack *Stk,     int capacity_ctor, const char* stk_name,
                 const char* file_name, int stk_line                            )
{
    Stk->canary_left  = LEFT_CANARY;
    Stk->canary_right = RIGHT_CANARY;
    Stk->capacity_Stk = capacity_ctor;
    Stk->size_Stk = 0;

    (Stk->Stack_info).name = stk_name;
    (Stk->Stack_info).file = file_name;
    (Stk->Stack_info).line = stk_line;
    (Stk->Stack_info).error_codes = 0;
    (Stk->Stack_info).cur_status = "OK";

    if (capacity_ctor >= 0)
    {
        Stk->buffer_stk = (double*) calloc (1, capacity_ctor * sizeof (double));
    }

    Stk->hash = calculate_hash (Stk);
    verificate_stack (Stk, Stk->hash);

    return 0;
}

//-----------------------------------------------------------------------------

void stack_dtor (struct Stack *Stk)
{
    int new_hash = calculate_hash (Stk);

    verificate_stack (Stk, new_hash);

    free (Stk->buffer_stk);

    Stk->hash = -1;
}

//-----------------------------------------------------------------------------

void stack_push (struct Stack *Stk, double elem)
{
    int new_hash = calculate_hash (Stk);

    verificate_stack (Stk, new_hash);

    if(Stk->size_Stk + 1 > Stk->capacity_Stk)
    {
        stack_resize (Stk, Stk_INCREASE);
    }

    Stk->buffer_stk[Stk->size_Stk] = elem;

    (Stk->size_Stk)++;

    Stk->hash = calculate_hash (Stk);
}

//-----------------------------------------------------------------------------

void stack_resize (struct Stack *Stk, int opt_resize)
{
    if(opt_resize == Stk_INCREASE)
    {
        if(Stk->capacity_Stk == 0)
        {
            Stk->capacity_Stk = 2;
        }

        Stk->capacity_Stk *= 2;

        Stk->buffer_stk = (double*) recalloc (Stk->buffer_stk, Stk->capacity_Stk, Stk->size_Stk, sizeof (double));
    }

    else if(opt_resize == Stk_DECREASE)
    {
        Stk->capacity_Stk /= 2;

        Stk->buffer_stk = (double*) recalloc (Stk->buffer_stk, Stk->capacity_Stk, Stk->size_Stk, sizeof (double));
    }

    Stk->hash = calculate_hash (Stk);
}

//-----------------------------------------------------------------------------

double stack_pop (struct Stack *Stk)
{
    int new_hash = calculate_hash (Stk);

    verificate_stack (Stk, new_hash);

    double elem_del = Stk->buffer_stk[Stk->size_Stk - 1];
    Stk->buffer_stk[Stk->size_Stk - 1] = 0;

    Stk->size_Stk--;

    if(Stk->size_Stk <= Stk->capacity_Stk / 4)
    {
        stack_resize (Stk, Stk_DECREASE);
    }

    Stk->hash = calculate_hash (Stk);

    return elem_del;
}

//-----------------------------------------------------------------------------

void verificate_stack (struct Stack *Stk, int new_hash)
{
    check_errors (Stk, new_hash);

    if ((Stk->Stack_info).error_codes != 0)
    {
        (Stk->Stack_info).cur_status = "ERROR";
    }
}

//-----------------------------------------------------------------------------

int calculate_hash (struct Stack *Stk)
{
    int sum = 0;
    int hash_par = HASH_CONST;

    for(int i = 0; i < Stk->capacity_Stk; i++)
    {
        sum += (int)(Stk->buffer_stk[i] * HASH_BASE * hash_par);
        sum %= UINT_MAX;
        hash_par *= HASH_CONST;
    }

    return sum;
}

//-----------------------------------------------------------------------------

void debug_stack (struct Stack *Stk)
{
    handle_errors  (Stk);
    stack_dump_    (Stk);
}

//-----------------------------------------------------------------------------

void handle_errors (struct Stack *Stk)
{
    if((Stk->Stack_info).error_codes == 0)
    {
        printf ("OK\n");
    }

    else
    {
        for(int i = 0; i < NUM_OF_MIS; i++)
        {
            if((Stk->Stack_info).error_codes & error_arr[i].error_code)
            {
                printf ("%d %s\n", error_arr[i].error_code, error_arr[i].error_output);
            }
        }
    }
}

//-----------------------------------------------------------------------------

void stack_dump_ (struct Stack *Stk)
{
    FILE *log_file = fopen ("../dump/log.txt", "w+");

    fprintf (log_file,
             "%s[%p](%s) at %s, LINE - %d \n"
             "{                           \n"
             "    canary_open  = %x       \n"
             "    canary_close = %x       \n"
             "    hash         = %x       \n"
             "    size_Stk     = %d       \n"
             "    capacity_Stk = %d       \n"
             "                            \n"
             "    buffer_stk[%p]          \n"
             "    {                       \n",
             (Stk->Stack_info).name + 1,    Stk,
             (Stk->Stack_info).cur_status, (Stk->Stack_info).file,
             (Stk->Stack_info).line,
             Stk->canary_left,
             Stk->canary_right,
             Stk->hash,
             Stk->size_Stk,
             Stk->capacity_Stk,
             Stk->buffer_stk);

    for(int pos = 0; pos < Stk->capacity_Stk; pos++)
    {
        fprintf (log_file,
                 "          [%d] = %lg        \n",
                 pos, Stk->buffer_stk[pos]);
    }

    fprintf (log_file,
             "    }                       \n"
             "}                           \n");

    fclose (log_file);
}

//-----------------------------------------------------------------------------

void check_errors (struct Stack *Stk, int new_hash)
{
    if(Stk->canary_left != LEFT_CANARY)    (Stk->Stack_info).error_codes |= ERR_CAN_1;
    if(Stk->canary_right != RIGHT_CANARY)  (Stk->Stack_info).error_codes |= ERR_CAN_2;
    if(Stk->buffer_stk == NULL)            (Stk->Stack_info).error_codes |= ERR_MEMBUF;
    if(Stk->capacity_Stk < Stk->size_Stk)  (Stk->Stack_info).error_codes |= ERR_OVERF;
    if(Stk->capacity_Stk < 0)              (Stk->Stack_info).error_codes |= ERR_CAP;
    if(Stk->size_Stk < 0)                  (Stk->Stack_info).error_codes |= ERR_SIZE;
    if(Stk == NULL)                        (Stk->Stack_info).error_codes |= ERR_MEMStk;
    if(Stk->hash != new_hash)              (Stk->Stack_info).error_codes |= ERR_HASH;
}

//-----------------------------------------------------------------------------

void *recalloc (void *buffer, int capacity, int size, int size_of_type)
{
    char *pointer = (char*) realloc ((char*) buffer, capacity * size_of_type);

    if(capacity > size)
    {
        memset (pointer + size * size_of_type, '\0', (capacity - size) * size_of_type);
    }

    return (void*) pointer;
}

//-----------------------------------------------------------------------------


