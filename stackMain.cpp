#include <stdio.h>
#include <stdlib.h>
#include "stack3.h"

// #define DEBUG

int main()
{
    Stack_t stk = {};
    Hash_struct hash = {};

    stackCtor(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif
    
    StackElem_t new_element = 10.878484;
    for (int i = 0; i < 200; i++)
    {
        stackPush(&stk, new_element, &hash);    
    }

    stackDump(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif
    stackPush(&stk, new_element, &hash);
    stackDump(&stk, &hash);
    //stk.data[0] = 666;
    for (int i = 0; i < 20; i++)
    {
        stackPop(&stk, &hash);
    }
    stackDump(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif

    stackDestroy(&stk, &hash);
}