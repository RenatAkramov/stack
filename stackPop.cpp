#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

int stackPop(Stack_t* stk, Hash_struct* hash)
{
    StackElem_t x = 0;
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif

    if ( stk->size == stk->capacity / 4)
    {
        (stk->data)[stk->capacity + 1] = 0;

        stk -> capacity = (stk -> capacity) / 2;

        stk -> data = (StackElem_t*) realloc(stk -> data, stk -> capacity * sizeof(double));

        (stk->data)[stk->capacity + 1] = right_stk_canary_values;
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }

    (stk -> data)[stk -> size] = x;

    int size_old = stk->size;

    stk -> size = stk -> size - 1;

    hash->hash_array = hash_func_array(stk);

    hash->hash_struct = hash_func_struct(stk);

    if (size_old - stk->size != 1 || compare((stk -> data)[size_old], x) != 0)
    {
        stk->error_code[stk->error_code_nume] = ERROR_POP;
        stk->error_code_nume++;
    }
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    return (double) x;
    
}