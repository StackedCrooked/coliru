#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int a = -10;
    int b = 4;
    int q = 0;
    int r = 0;
    asm volatile
    (
        "mov eax, %2;"
        "mov ebx, %3;"
        "cdq;"
        "idiv ebx;"
        "test edx, edx;"
        "jge 1f;"
        "dec eax;"
        "add edx, ebx;"
        "1:"
        : "=a" (q), "=d" (r)
        : "g" (a), "g" (b)
    );
    
    cout << "Quotient:" << q << ", Remainder:" << r << endl;
}
