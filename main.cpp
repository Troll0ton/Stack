#include "stack.h"

//-----------------------------------------------------------------------------

int main ()
{
    FILE *file_out = fopen ("log.txt", "w+");

    setlocale (LC_ALL, "Russian");

    struct Stack *stk1 = NULL;

    stack_ctor (&stk1, 40);// == 0 || Error ("");

    for(int i = 1000; i < 1008; i++)
    {
        stack_push (stk1, i);
    }

    for(int i = 0; i < 6; i++)
    {
        stack_pop (stk1);
    }

    debug_stack (stk1);

    stack_dtor (stk1);

    return 0;
}

//-----------------------------------------------------------------------------

