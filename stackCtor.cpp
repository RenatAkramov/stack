#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

int stackCtor(Stack_t* stk, Hash_struct* hash)
{
    stk->capacity = START_SIZE;

    stk->data = (double*) calloc(stk->capacity + 2, sizeof(double));
     (stk->data)[-1] = left_stk_canary_values;

    (stk->data)[stk->capacity + 1] = right_stk_canary_values;

    stk->size = 0;

    stk->amount_error = 0; 

    hash->hash_array = 0;

    hash->hash_struct = 0;

    for (int i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = NULL_ELEMENT_DATA;
    }

    hash->hash_array = hash_func_array(stk);

    hash->hash_struct = hash_func_struct(stk);

    if (stk == NULL || stk->data == NULL || stk->size != 0)
    {
        stk->error_code[stk->error_code_nume] = ERROR_CTOR;
        stk->error_code_nume++;

        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }
    else
    {
        return OKEY;
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }

}