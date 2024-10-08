#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include <math.h>

typedef double StackElem_t;
#define DEBUG

enum hui
{
    OKEY                      = 0,
    ERROR_CTOR                = 1,
    ERROR_PUSH                = 2,
    ERROR_POP                 = 3,
    ERROR_DESTROY             = 4,
    ERROR_left_struct_canary  = 5,
    ERROR_right_struct_canary = 6,
    ERROR_left_stk_canary     = 7,
    ERROR_right_stk_canary    = 8,
    ERROR_hash_array          = 9,
    START_SIZE                = 10,
    NULL_ELEMENT_DATA         = 0xBEDA   //0xDEAD
};

enum canary
{
    left_stk_canary_values           = 0xDEAD,
    right_stk_canary_values          = 0xDEAD,
    left_struct_canary_values        = 0xDEAD,
    right_struct_canary_values       = 0xDEAD
};

struct Stack_t
{
    StackElem_t  left_struct_canary  = left_struct_canary_values;
    StackElem_t* data                  {};
    int          size                = 0;
    int          capacity            = 0;
    int          error_code[10]      = {0};
    int          error_code_nume     = 0;
    int          amount_error        = 0;
    StackElem_t  right_struct_canary = right_struct_canary_values;
};

struct Hash_struct
{
    unsigned long long hash_array  = 0;
    unsigned long long hash_struct = 0;
};

int  stackPop(Stack_t* stk, Hash_struct* hash);

int  stackPush(Stack_t* stk, StackElem_t new_element, Hash_struct* hash);

int  stackCtor(Stack_t* stk, Hash_struct* hash); // static

void stackDump(Stack_t* stk, Hash_struct* hash);

int  stackDestroy(Stack_t* stk, Hash_struct* hash);

int  stackOkey(Stack_t* stk, Hash_struct* hash);

void stackCheck(Stack_t* stk, Hash_struct* hash);

int compare(StackElem_t a, StackElem_t b);

unsigned long long hash_func_array(Stack_t* stk, Hash_struct* hash);

unsigned long long hash_func_struct(Stack_t* stk, Hash_struct* hash);

int main()
{
    Stack_t stk = {};
    Hash_struct hash = {};
    stackCtor(&stk, &hash);
    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif
    StackElem_t new_element = 10.89;
    stackPush(&stk, new_element, &hash); // передаешь значение

    stackDump(&stk, &hash);

    stackPop(&stk, &hash);

    stackDump(&stk, &hash);

    #ifdef DEBUG
    stackCheck(&stk, &hash);
    #endif

}

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

    hash->hash_array = hash_func_array(stk, hash);

    hash->hash_struct = hash_func_struct(stk, hash);

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

int stackPush(Stack_t* stk, StackElem_t new_element, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    if (stk->size == stk->capacity)
    {
        (stk->data)[stk->capacity + 1] = 0;

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

    hash->hash_array = hash_func_array(stk, hash);

    hash->hash_struct = hash_func_struct(stk, hash);

    if (stk->size - size_old != 1 || compare((stk -> data)[stk -> size - 1], new_element) != 0 || stk->size > stk->capacity)
    {
        stk->error_code[stk->error_code_nume] = ERROR_PUSH;
        stk->error_code_nume++;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif

}

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

    hash->hash_array = hash_func_array(stk, hash);

    hash->hash_struct = hash_func_struct(stk, hash);

    if (size_old - stk->size != 1 || compare((stk -> data)[size_old], x) != 0)
    {
        stk->error_code[stk->error_code_nume] = ERROR_POP;
        stk->error_code_nume++;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
}

int stackDestroy(Stack_t* stk, Hash_struct* hash)
{
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
    free(stk -> data);

    stk->size = 0xDEAD;

    stk->capacity = 0xDEAD;

    hash->hash_array = hash_func_array(stk, hash);
    hash->hash_struct = hash_func_struct(stk, hash);

    if (stk->data != NULL || stk->size != 0xDEAD || stk->capacity !=0xDEAD)
    {
        stk->error_code[stk->error_code_nume] = ERROR_DESTROY;
        stk->error_code_nume++;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk, hash);
    #endif
}

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
    printf("hash data: %llx", hash->hash_array);
    printf("\n");
    printf("hash struct: %llx\n\n", hash->hash_struct);
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
    if (hash->hash_array != hash_func_array(stk, hash))
    {
        printf("ERROR 9 ERROR in hash, Value hash is incorrect");
        stk->error_code[stk->error_code_nume] = ERROR_hash_array;
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
    if (fabs(a - b) < e)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}


unsigned long long hash_func_array(Stack_t* stk, Hash_struct* hash)
{
    unsigned long hash_calculation = 0x5381;
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
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
        j = 0;
    }
    return hash_calculation;
}

unsigned long long hash_func_struct(Stack_t* stk, Hash_struct* hash)
{
    unsigned long long hash_calculation = 0x5381;
    int c = 0x0, j = 0;
    char str_stk_element[62] = {};

    hash_calculation = hash_func_array(stk, hash);

    printf("%llx\n", hash_calculation);
    for (int i = 0; i < 10; i++)
    {
        //printf("%lg\n", (stk->data)[i]);
        sprintf(str_stk_element,"%d", (stk->error_code)[i]);//stk->data[i]); 
        //printf("%s \n",str_stk_element);         
        while (str_stk_element[j])
        {
            c = str_stk_element[j];
            printf("%x \n",c);
            //printf("%c\n",c);
            //hash_calculation = hash_calculation * 33 + c;
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
        j = 0;
        printf("\n");
    }
    printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->size));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->capacity));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->error_code_nume));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    printf("%llx\n", hash_calculation);
    sprintf(str_stk_element,"%d", (stk->amount_error));
    while (str_stk_element[j])
        {
            c = str_stk_element[j];
            //printf("%c\n",c);
            hash_calculation = ((hash_calculation << 5) - hash_calculation) ^ c; /* hash * 33 + c */
            j++;        
        }
    j = 0;
    printf("%llx\n", hash_calculation);
    return hash_calculation;
        
}