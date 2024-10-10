#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

int stackDestroy(Stack_t* stk, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    free(stk->data);

    stk->size = 0xBEDA;

    stk->capacity = 0xBEDA;

    if (stk->size != 0xBEDA || stk->capacity !=0xBEDA)
    {
        stk->error_code[stk->error_code_nume] = ERROR_DESTROY;
        stk->error_code_nume++;
    }
    else
    {
        return OKEY;
    }
}
