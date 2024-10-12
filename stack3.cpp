#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

//#define DEBUG

/*int main()
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
}*/

int stackCtor(Stack_t* stk, Hash_struct* hash)
{
    stk->capacity = START_SIZE;
    stk->size = 0;
    stk->data = {};
    stk->amount_error = 0;
    stk->error_code[10] = {0};
    stk->error_code_nume = 0;
    stk->left_struct_canary = left_stk_canary_values;
    stk->right_struct_canary = right_stk_canary_values;

    stk->data = (StackElem_t*) calloc(stk->capacity + 2, sizeof(double)) + 1;
    (stk->data)[-1] = left_stk_canary_values;

    (stk->data)[stk->capacity + 1] = right_stk_canary_values;

    stk->size = 0;

    stk->amount_error = 0; 

    hash->hash_array = 0;

    hash->hash_struct = 0;

    /*for (int i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = NULL_ELEMENT_DATA;
    }*/

    hash->hash_array = hash_func_array(stk);

    hash->hash_struct = hash_func_struct(stk);

    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif

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
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
        return OKEY;
    }

}

int stackPush(Stack_t* stk, StackElem_t new_element, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    if (stk->size == stk->capacity)
    {
        (stk->data)[stk->capacity + 1] = 0; //define для обнурения канарейки 
        stk->capacity = stk->capacity * 2; //a *= 2

        size_t new_size_byte = (stk->capacity + 3) * sizeof(StackElem_t);
        stk->data = (StackElem_t*) realloc((stk->data - 1), new_size_byte) + 1;
        (stk->data)[stk->capacity + 1] = right_stk_canary_values;

        /*#ifdef DEBUG
        stackCheck(stk, hash);
        #endif*/
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
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }
    else
    {
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
        return OKEY;
    }
}

int stackPop(Stack_t* stk, Hash_struct* hash)
{
    int x = 0;
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif

    if ( stk->size == stk->capacity / 4 && stk->capacity > 10)
    {
        (stk->data)[stk->capacity] = 0;

        stk -> capacity = (stk -> capacity) / 2;

        stk -> data = (StackElem_t*) realloc(stk -> data - 1, (stk -> capacity + 2) * sizeof(double)) + 1;
        (stk->data)[stk->capacity + 1] = right_stk_canary_values;
        hash->hash_array = hash_func_array(stk);
        hash->hash_struct = hash_func_struct(stk);
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }

    x = (stk -> data)[stk -> size - 1];

    int size_old = stk->size;

    stk -> size = stk -> size - 1;

    hash->hash_array = hash_func_array(stk);

    hash->hash_struct = hash_func_struct(stk);

    if (stk->size < 0)
    {
        stk->error_code[stk->error_code_nume] = ERROR_POP;
        stk->error_code_nume++;
        #ifdef DEBUG
        stackCheck(stk, hash);
        #endif
    }
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    return x;
    
}

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

void stackDump(Stack_t* stk, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
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
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
}

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
    /*if (compare((stk->data)[-1], left_stk_canary_values) != 0)
    {
        printf("ERROR 7 ERROR in left_stk_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_left_stk_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }*/
    if (compare((stk->data)[stk->capacity + 1], right_stk_canary_values) != 0)
    {
        printf("ERROR 8 ERROR in right_stk_canary\n ");
        stk->error_code[stk->error_code_nume] = ERROR_right_stk_canary;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (hash->hash_array != hash_func_array(stk))
    {
        printf("ERROR 9 ERROR in hash array, Value hash array is incorrect\n");
        stk->error_code[stk->error_code_nume] = ERROR_hash_array;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    if (hash->hash_struct != hash_func_struct(stk))
    {
        printf("ERROR 10 ERROR in hash struct, Value hash struct is incorrect\n");
        stk->error_code[stk->error_code_nume] = ERROR_hash_struct;
        stk->error_code_nume++;
        stk->amount_error++;
    }
    return 1;
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


unsigned long long hash_func_array(Stack_t* stk)
{
    unsigned long hash_calculation = 0x1505;
    int c = 0x0, j = 0;
    char str_stk_data_element[62] = {};
    for (int i = 0; i < stk->size; i++)
    {
        //printf("%lg\n", (stk->data)[i]);
        sprintf(str_stk_data_element,"%lg", (stk->data)[i]);//stk->data[i]); 
        //printf("%shui \n",str_stk_data_element);         
        while (str_stk_data_element[j])
        {
            c = str_stk_data_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
        j = 0;
    }
    return hash_calculation;
}

unsigned long long hash_func_struct(Stack_t* stk)
{
    unsigned long long hash_calculation = 0x1505;
    int c = 0x0, j = 0;
    char str_stk_element[64] = {};

    hash_calculation = hash_func_array(stk);

    //printf("%llx\n", hash_calculation);
    for (int i = 0; i < 10; i++)
    {
        //printf("%lg\n", (stk->data)[i]);
        sprintf(str_stk_element,"%d", (stk->error_code)[i]);//stk->data[i]); 
        //printf("%s \n",str_stk_element);         
        while (str_stk_element[j])
        {
            c = str_stk_element[j];
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
        j = 0;
    }
    //printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->size));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    //printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->capacity));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    //printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->error_code_nume));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    //printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->amount_error));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) + hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    //printf("%llx\n", hash_calculation);
    return hash_calculation;
        
}