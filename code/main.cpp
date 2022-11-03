#include "../include/stack.h"

//-----------------------------------------------------------------------------

int main ()
{
    Stack Stk = { 0 };

    stack_ctor (&Stk, 2);

    for(int i = 1000; i < 1200; i++)
    {
        stack_push (&Stk, i);
    }

    for(int i = 0; i < 20; i++)
    {
        stack_pop (&Stk);
    }

    debug_stack (&Stk);

    stack_dtor (&Stk);

    return 0;
}

//-----------------------------------------------------------------------------

