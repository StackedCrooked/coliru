#include <iostream>

const char * some_function(void)
{
    const char* local_string = "Hello, world!";
    static const char * static_pointer = local_string;    // Here is the bug

    std::cout << static_pointer << std::endl;

    return local_string;    // Here is a related bug
}

void function_nest(void)
{
    int i = 5;
    // std::cout << i << std::endl;
    some_function();
}

int main(int argc, char ** argv)
{
    some_function();
    function_nest();
    some_function();
}