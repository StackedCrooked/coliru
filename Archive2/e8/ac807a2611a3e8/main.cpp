#include <iostream>
using namespace std;

int main () {
     char s[] = "hello";
     char t[] = "house";
     while (*s++ = *t++);
     cout << s;
     return 0;
}