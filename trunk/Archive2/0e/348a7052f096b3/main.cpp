#include <iostream>

const char * as_array(void)
{
    const char local_string[] = "Hello, world!";
    return local_string;
}

const char* as_pointer(void) {
    const char* local_string = "Hello, world!";
    return local_string;
}

int main(int argc, char ** argv)
{
    as_array();
    as_pointer();
}