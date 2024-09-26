#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include <math.h>

typedef double StackElem_t;


/*enum Constant
{
    ERROR     = 1,
    OKEY      = 0,
    STARTSIZE = 10
};*/

struct Stack_t
{
    StackElem_t* data;

    int          size;

    int      capacity;

};



int stackPop(Stack_t* stk);// убрать элемент в х убрать лишнюю память реалоком на половине

int stackPush(Stack_t* stk);// добавить элкменты добавить память реалоком

int stackCtor(Stack_t* stk, int* STARTSIZE);// создать стэк первоночально

int stackDump(Stack_t* stk);// куча принтов

int stackDestroy(Stack_t* stk); //очищает всю память делает фри

int stackOkey(Stack_t* stk);// проверка что все ок куча ифов



int main()
{
    int STARTSIZE = 10;
    Stack_t stk = {};
    stackCtor(&stk, &STARTSIZE);
    if (stackOkey(&stk) == 0)
    {
        stackPush(&stk);
        stackDump(&stk);
        stackPop(&stk);
        stackDump(&stk);
    }
    else
    {
        stackDump(&stk);
        exit(1);
    }
}

int stackCtor(Stack_t* stk, int* STARTSIZE)
{
    //int STARTSIZE = 10;
    stk -> capacity = *STARTSIZE;

    stk -> data = (double*) calloc(stk -> capacity, sizeof(double));

    stk -> size = 0;

}

int stackPush(Stack_t* stk)
{
    StackElem_t y = 10.0;

    if (stk -> size == stk -> capacity)
    {
        stk -> capacity = (stk -> capacity) * 2;

        stk -> data = (StackElem_t*) realloc(stk -> data, stk -> capacity * sizeof(double));
    }

    (stk -> data)[stk -> size] = y;

    stk -> size = stk -> size + 1;

}

int stackPop(Stack_t* stk)
{
    StackElem_t x = 0;

    if ( stk -> size == stk -> capacity / 4)
    {
        stk -> capacity = (stk -> capacity) / 2;

        stk -> data = (StackElem_t*) realloc(stk -> data, stk -> capacity * sizeof(double));
    }

    (stk -> data)[stk -> size] = x;

    stk -> size = stk -> size - 1;

}

int stackDestroy(Stack_t* stk)
{
    free(stk -> data);

    stk -> size = 0;

    stk -> capacity = 0;
}

int stackDump(Stack_t* stk)
{
    printf("Element in data:");

    for (int i = 0; i < stk->size; i++)
    {
        printf("%lg ", (stk->data)[i]);
    }

    printf("\n size:");
    printf("%d", stk->size);

    printf("\n capacity:");
    printf("%d\n", stk->capacity);
}

int stackOkey(Stack_t* stk)
{
    if (stk->data == NULL)
    {
        printf("ERROR 1 data = NULL");

        return 1;
    }
    else
    {
        return 0;
    }
}

