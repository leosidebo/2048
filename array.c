#include "array.h"
#include <stdlib.h>


/* External functions */


//Dynamic allocated array, return it.
Array *array_create(int n1, int n2)
{
    Array *temp_array = malloc(sizeof(*temp_array));

    //Sets value of the rows and columns.
    temp_array->n1 = n1;

    temp_array->n2 = n2;

    //Zeroed allocated array
    temp_array->data = calloc(n1 * n2, sizeof(int));

    return temp_array;
}

//free all allocated memory.
void array_destroy(Array *arr)
{
    free(arr->data);
    free(arr);
}


//Return the rows
int array_rows(const Array *arr)
{
    return arr->n1;
}


//Return the columns
int array_columns(const Array *arr)
{
    return arr->n2;
}


//Get the value at the index.
int array_get(const Array *arr, int i1, int i2)
{
    //Get the value at the index. [current rows * max columns + current columns]
    return arr->data[i1 * array_columns(arr) + i2];
}


void array_set(Array *arr, int i1, int i2, int value)
{
    //Set the value at the index. [rows * max columns + columns]
    arr->data[i1 * array_columns(arr) + i2] = value;
}
