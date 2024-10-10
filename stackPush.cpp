#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

int stackPush(Stack_t* stk, StackElem_t new_element, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    if (stk->size == stk->capacity)
    {
        (stk->data)[stk->capacity + 1] = 0; //define для обнурения канарейки 

        stk->capacity *= 2; //a *= 2

        stk->data = (StackElem_t*) realloc(stk->data, (stk->capacity + 2) * sizeof(double));

        (stk->data)[stk->capacity + 1] = right_stk_canary_values;
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }

    (stk -> data)[stk -> size] = new_element;

    int size_old = stk->size;

    stk->size = stk->size + 1;

    hash->hash_array = hash_func_array(stk);

    hash->hash_struct = hash_func_struct(stk);

    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif

    if (stk->size - size_old != 1 || compare((stk -> data)[stk -> size - 1], new_element) != 0 || stk->size > stk->capacity)
    {
        stk->error_code[stk->error_code_nume] = ERROR_PUSH;
        stk->error_code_nume++;
    }
    else
    {
        return OKEY;
    }
}
