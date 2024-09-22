#include <stdio.h>
// A normal function with an int parameter
// and void return type
void fun(int a, char b)
{
    printf("Value of a is %d (%c)\n", a, b);
}

int main(int argc, char **argv)
{
    // fun_ptr is a pointer to function fun()
    void (*fun_ptr)(int, char) = &fun; // after the *fun_ptr, on the second parenthesis we find the arguments of the function fun()
    void (*fun_ptr_2)(int, char) = fun;

    /* The above line is equivalent of following two
    void (*fun_ptr)(int);
    fun_ptr = &fun;
    */

    // Invoking fun() using fun_ptr
    (*fun_ptr)(10, 'j');
    fun_ptr_2(5, 'a');

    return 0;
}