#ifndef ARRAY_H
#define ARRAY_H


/**
 * @defgroup        array_h  OU1b Fält
 * @author          Nils L
 * @author          dv20nls
 * @author          nili0132
 * @date            2020-11-29
 *
 * @brief Contains declarations for array.c
 *
 * Contains declarations for functions defined in array.c and
 * for a data structure.
 *
 *@{
 */


/**
 * @brief The type for a 2D array.
 *
 * Integer n1. The number of rows the array has.
 * Integer n2. The number of columns the array has.
 * Integer pointer data. Points to the value the array is to store.
 *
 */
typedef struct array
{
    int n1;
    int n2;
    int *data;
} Array;


/**
 * @brief Create and return a zero array of size n1 rows by n2 columns.
 *
 *
 * Allocates memory for the array of size rows*columns.
 * Sets its row and columns to the ones provided by the in parameters.
 *
 * @param n1        The number of rows.
 * @param n2        The number of columns.
 * @return          A zeroed array.
 */
Array *array_create(int n1, int n2);


/**
 * @brief Destroy an array.
 *
 * Free the allocated memory for the array.
 *
 * @param *arr      Array pointer.
 * @return          -
 */
void array_destroy(Array *arr);


/**
 * @brief Get the number of rows.
 *
 * Get the number of rows arr has and return it.
 *
 * @param *arr      Array pointer.
 * @return          The number of rows arr has.
 */
int array_rows(const Array *arr);


/**
 * @brief Get the number of columns.
 *
 * Get the number of columns arr has and return it.
 *
 * @param *arr      Array pointer.
 * @return          The number of columns arr has.
 */
int array_columns(const Array *arr);


/**
 * @brief Return the value at row i1 and column i2 (zero-based indexing).
 *
 * Get the index, then get the value at the index.
 * Return the value.
 *
 * @param *arr      Array pointer.
 * @param i1        Integer containing the number of rows.
 * @param i2        Integer containing the number of columns.
 * @return          An Integer containing the value.
 */
int array_get(const Array *arr, int i1, int i2);


/**
 * @brief Set the value at row i1 and column i2 (zero-based indexing).
 *
 * Get the index.
 * Set the inparam value at the index.
 *
 * @param *arr      Array pointer.
 * @param i1        Integer containing the number of rows.
 * @param i2        Integer containing the number of columns.
 * @param value     Integer with the value to be set.
 * @return          -
 */
void array_set(Array *arr, int i1, int i2, int value);

#endif /* ARRAY_H */

/**
 * @}
 */
