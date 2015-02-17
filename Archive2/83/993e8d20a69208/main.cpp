#include <iostream>
#include <string>

using namespace std;

void foo(void **v) { 
    wchar_t *t = L"String is changed!"; 
    *((wchar_t**)v) = t; 
} 

wchar_t *ChangeMe = L"Change me.";

int main () {
    wcout << ChangeMe << endl;
    foo((void**)&ChangeMe);
    wcout << ChangeMe << endl;
    return 0; 
}