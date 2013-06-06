#include <iostream>

typedef void(*atexit_fun)(void);

atexit_fun myatexit_fun = nullptr;

void myatexit(atexit_fun f)
{
   myatexit_fun = f;
}

void invoke_myatexit()
{
    (*myatexit_fun)();
}

void dummy()
{
   std::cout << "dummy()\n";
}

int main()
{
    myatexit(&dummy);
    invoke_myatexit();
}
