#include <exception>
#include <string>
#include <stdio.h>
#include <assert.h>

void dd() throw()
{
    throw "asdf";
    //assert(0);
}

int main() {
    dd();
    return 0;
}