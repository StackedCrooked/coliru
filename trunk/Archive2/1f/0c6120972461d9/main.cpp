#include <iostream>

namespace STD
{
class BASIC_STRING {};
typedef BASIC_STRING STRING;
}

int main() {
    STD::STRING* a = new STD::STRING();
    a->~STRING();
}