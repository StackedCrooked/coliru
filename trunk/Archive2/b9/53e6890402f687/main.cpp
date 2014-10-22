#include <iostream>
using namespace std;
 
struct S
{
    int i[2] = { 42, 100500 };
};
     
int main() {
    S s;
    cout << s.i[0] << endl; // выводит 42
    return 0;
}