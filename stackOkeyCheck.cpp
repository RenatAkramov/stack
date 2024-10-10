#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

int stackOkey(Stack_t* stk, Hash_struct* hash)
{
    for (int i = 0; i < 10; i++)
    {
        if (stk->error_code[i] == ERROR_PUSH)
        {
            printf("ERROR 2 ERROR in PUSH\n");

            stk->amount_error++;
        }
        if (stk->error_code[i] == ERROR_CTOR)
        {
            printf("ERROR 1 ERROR in CTOR\n");

            stk->amount_error++;
        }
        if (stk->error_code[i] == ERROR_POP)
        {
            printf("ERROR 3 ERROR in POP\n");

           stk->amount_error++;
        }
        if (stk->error_code[i] == ERROR_DESTROY)
        {
            printf("ERROR 4 ERROR in DESTROY\n");

            stk->amount_error++;
        }
    } 
    if (compare(stk->left_struct_canary , left_struct_canary_values) != 0)
    {
        printf("ERROR 5 ERROR in left_struct_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_left_struct_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (compare(stk->left_struct_canary , right_struct_canary_values) != 0)
    {
        printf("ERROR 6 ERROR in right_struct_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_right_struct_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (compare((stk->data)[-1], left_stk_canary_values) != 0)
    {
        printf("ERROR 7 ERROR in left_stk_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_left_stk_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (compare((stk->data)[stk->capacity + 1], right_stk_canary_values) != 0)
    {
        printf("ERROR 8 ERROR in right_stk_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_right_stk_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (hash->hash_array != hash_func_array(stk))
    {
        printf("ERROR 9 ERROR in hash array, Value hash array is incorrect");
        stk->error_code[stk->error_code_nume] = ERROR_hash_array;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (hash->hash_struct != hash_func_struct(stk))
    {
        printf("ERROR 10 ERROR in hash struct, Value hash struct is incorrect");
        stk->error_code[stk->error_code_nume] = ERROR_hash_struct;
        stk->error_code_nume++;
        stk->amount_error++;
    }
}

void stackCheck(Stack_t* stk, Hash_struct* hash)
{
    stackOkey(stk, hash);
    if (stk->amount_error != 0)
    {
        stackDump(stk, hash);
        exit(1);
    }
}

int compare(StackElem_t a, StackElem_t b)
{
    double e = 0.0000000001;
    if (fabs((double) a - (double) b) < e)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}