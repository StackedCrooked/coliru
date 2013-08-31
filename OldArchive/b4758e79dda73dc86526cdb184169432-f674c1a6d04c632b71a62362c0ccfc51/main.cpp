#include <iostream>

void writeFoo(std::ostream &out)
{
  out << "somedata to display to the screen";
}

int main() {
    writeFoo(std::cout);
}