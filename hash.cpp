#include <stdio.h>
#include <stdlib.h>
#include <TXLib.h>
#include "stack3.h"

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