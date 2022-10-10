#include "stack.h"
#include "error_data.h"

//-----------------------------------------------------------------------------

int main ()
{
    setlocale (LC_ALL, "Russian");

    struct Stack *stk1 = NULL;

    stack_ctor (&stk1, 40);// == 0 || Error ("");

    for(int i = 1000; i < 1009; i++)
    {
        stack_push (stk1, i);
    }

    stack_pop  (stk1);

    debug_stack (stk1);

    stack_dtor (stk1);

    return 0;
}

//-----------------------------------------------------------------------------

