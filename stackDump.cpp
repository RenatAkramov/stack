#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

void stackDump(Stack_t* stk, Hash_struct* hash)
{
    printf("Element in data: ");

    for (int i = 0; i < stk->size; i++)
    {
        printf("%lg ", (stk->data)[i]);
    }

    printf("\n size: %d", stk->size);
    
    printf("\n capacity: %d\n", stk->capacity);

    printf("error_code_numm: %d\n",stk->error_code_nume);

    printf("amount error: %d\n", stk->amount_error);

    printf("error_code:");
    for (int i = 0; i < 10; i++)
    {
        printf("%d", stk->error_code[i]);
    }
    printf("\n");
    printf("hash data: %llx\n", hash->hash_array);
    
    printf("hash struct: %llx\n\n", hash->hash_struct);
}