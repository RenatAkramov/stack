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
    START_SIZE                = 10   //0xDEAD
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
    StackElem_t* data {};
    int          size                = 0;
    int          capacity            = 0;
    int          error_code          = 0;
    StackElem_t  right_struct_canary = right_struct_canary_values;
};

int  stackPop(Stack_t* stk);

int  stackPush(Stack_t* stk, StackElem_t new_element);

int  stackCtor(Stack_t* stk); // static

void stackDump(Stack_t* stk);

int  stackDestroy(Stack_t* stk);

int  stackOkey(Stack_t* stk);

void stackCheck(Stack_t* stk);

int main()
{
    Stack_t stk = {};
    stackCtor(&stk);
    #ifdef DEBUG
    stackCheck(&stk);
    #endif
    StackElem_t new_element = 10;
    stackPush(&stk, new_element); // передаешь значение

    stackDump(&stk);

    stackPop(&stk);

    stackDump(&stk);

    #ifdef DEBUG
    stackCheck(&stk);
    #endif

}

int stackCtor(Stack_t* stk)
{
    stk->capacity = START_SIZE;

    stk->data = (double*) calloc(stk->capacity + 2, sizeof(double));

    (stk->data)[-1]= left_stk_canary_values;
    (stk->data)[stk->capacity + 1] = right_stk_canary_values;

    stk->size = 0;

    if (stk == NULL || stk->data == NULL || stk->size != 0)
    {
        stk->error_code = ERROR_CTOR;
        #ifdef DEBUG
        stackCheck(stk);
        #endif
    }
    else
    {
        return OKEY;
        #ifdef DEBUG
        stackCheck(stk);
        #endif
    }

}

int stackPush(Stack_t* stk, StackElem_t new_element)
{
    #ifdef DEBUG
    stackCheck(stk);
    #endif
    if (stk->size == stk->capacity)
    {
        (stk->data)[stk->capacity + 1] = 0;

        stk->capacity *= 2; //a *= 2

        stk->data = (StackElem_t*) realloc(stk->data, (stk->capacity + 2) * sizeof(double));

        (stk->data)[stk->capacity + 1] = right_stk_canary_values;
        #ifdef DEBUG
        stackCheck(stk);
        #endif
    }

    (stk -> data)[stk -> size] = new_element;

    int size_old = stk->size;

    stk->size = stk->size + 1;

    if (stk->size - size_old != 1 || (stk -> data)[stk -> size - 1] != new_element || stk->size > stk->capacity)
    {
        stk->error_code = ERROR_PUSH;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk);
    #endif

}

int stackPop(Stack_t* stk)
{
    StackElem_t x = 0;
    #ifdef DEBUG
    stackCheck(stk);
    #endif

    if ( stk->size == stk->capacity / 4)
    {
        (stk->data)[stk->capacity + 1] = 0;

        stk -> capacity = (stk -> capacity) / 2;

        stk -> data = (StackElem_t*) realloc(stk -> data, stk -> capacity * sizeof(double));

        (stk->data)[stk->capacity + 1] = right_stk_canary_values;
        #ifdef DEBUG
        stackCheck(stk);
        #endif
    }

    (stk -> data)[stk -> size] = x;

    int size_old = stk->size;

    stk -> size = stk -> size - 1;

    if (size_old - stk->size != 1 || (stk -> data)[size_old] != x)
    {
        stk->error_code = ERROR_POP;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk);
    #endif
}

int stackDestroy(Stack_t* stk)
{
    #ifdef DEBUG
    stackCheck(stk);
    #endif
    free(stk -> data);

    stk->size = 0xDEAD;

    stk->capacity = 0xDEAD;

    if (stk->data != NULL || stk->size != 0xDEAD || stk->capacity !=0xDEAD)
    {
        stk->error_code = ERROR_DESTROY;
    }
    else
    {
        return OKEY;
    }
    #ifdef DEBUG
    stackCheck(stk);
    #endif
}

void stackDump(Stack_t* stk)
{
    printf("Element in data: ");

    for (int i = 0; i < stk->size; i++)
    {
        printf("%lg ", (stk->data)[i]);
    }

    printf("\n size:");
    printf("%d", stk->size);

    printf("\n capacity:");
    printf("%d\n", stk->capacity);

    printf("error_code:");
    printf("%d\n", stk->error_code);
}

int stackOkey(Stack_t* stk)
{
    if (stk->error_code == ERROR_PUSH)
    {
        printf("ERROR 2 ERROR in PUSH\n");

        return ERROR_PUSH;
    }
    if (stk->error_code == ERROR_CTOR)
    {
        printf("ERROR 1 ERROR in CTOR\n");

        return ERROR_CTOR;
    }
    if (stk->error_code == ERROR_POP)
    {
        printf("ERROR 3 ERROR in POP\n");

        return ERROR_POP;
    }
    if (stk->error_code == ERROR_DESTROY)
    {
        printf("ERROR 4 ERROR in DESTROY\n");
        return ERROR_DESTROY;
    }
    if (stk->left_struct_canary != left_struct_canary_values)
    {
        printf("ERROR 5 ERROR in left_struct_canary ");
        return ERROR_left_struct_canary;
    }
    if (stk->right_struct_canary != right_struct_canary_values)
    {
        printf("ERROR 6 ERROR in right_struct_canary ");
        return ERROR_right_struct_canary;
    }
    if ((stk->data)[-1] != left_stk_canary_values)
    {
        printf("ERROR 7 ERROR in left_stk_canary ");
        return ERROR_left_stk_canary;
    }
    if ((stk->data)[stk->capacity + 1] != right_stk_canary_values)
    {
        printf("ERROR 8 ERROR in right_stk_canary ");
        return ERROR_right_stk_canary;
    }
    if (stk->error_code == 0)
    {
        return OKEY;
    }
    printf("%d", stk->error_code);

}

void stackCheck(Stack_t* stk)
{
    if (stackOkey(stk) != 0)
    {
        stackDump(stk);
        exit(1);
    }
}

