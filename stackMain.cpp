#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

#define DEBUG

int main()
{
    Stack_t stk = {};
    Hash_struct hash = {};

    stackCtor(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif
    
    StackElem_t new_element = 10.878484;
    stackPush(&stk, new_element, &hash); // передаешь значение

    stackDump(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif

    stackPop(&stk, &hash);

    stackDump(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif

    stackDestroy(&stk, &hash);
}