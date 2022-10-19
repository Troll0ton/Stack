#include "stack.h"

//-----------------------------------------------------------------------------

int main ()
{
    Stack stk1;

    stack_ctor (&stk1, 2);

    for(int i = 1000; i < 1040; i++)
    {
        stack_push (&stk1, i);
    }

    for(int i = 0; i < 20; i++)
    {
        stack_pop (&stk1);
    }

    debug_stack (&stk1);

    stack_dtor (&stk1);

    return 0;
}

//-----------------------------------------------------------------------------

