#include <iostream>
#include <stdarg>

int sum(int argnum, ...)
{
    va_list arguments;
    int i;
    int sum = 0;

    va_start(arguments, argnum); /* Needs last known character to calculate
                               the address of the other parameters */
    for(i = 0; i < argnum; ++i)
        sum += va_arg(arguments, int); /* use next argument */

    va_end(arguments);

    return sum;
}
    
int main()
{
    std::cout << "5 + 7 + 1 + 3 - 2 = " << sum(5, 5, 7, 1, 3, -2);

   return 0;
}