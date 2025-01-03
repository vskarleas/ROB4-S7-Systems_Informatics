/*
    Similar to qsort() [test4a.c], we can write our own functions that can be used for any data 
    type and can do different tasks without code redundancy. Below is an example search 
    function that can be used for any data type. In fact we can use this search function 
    to find close elements (below a threshold) by writing a customized compare function.
*/

#include <stdbool.h>
#include <stdio.h>

// A compare function that is used for searching an integer
// array
bool compare(const void* a, const void* b)
{
    return (*(int*)a == *(int*)b);
}

// General purpose search() function that can be used
// for searching an element *x in an array arr[] of
// arr_size. Note that void pointers are used so that
// the function can be called by passing a pointer of
// any type. ele_size is size of an array element
int search(void* arr, int arr_size, int ele_size, void* x,
           bool compare(const void*, const void*))
{
    // Since char takes one byte, we can use char pointer
    // for any type/ To get pointer arithmetic correct,
    // we need to multiply index with size of an array
    // element ele_size
    char* ptr = (char*)arr;

    int i;
    for (i = 0; i < arr_size; i++)
        if (compare(ptr + i * ele_size, x))
            return i;

    // If element not found
    return -1;
}

int main()
{
    int arr[] = { 2, 5, 7, 90, 70 };
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 7;
    printf("Returned index is %d ",
           search(arr, n, sizeof(int), &x, compare));
    return 0;
}
