#include <iostream>
 using namespace std;
//make function factory and use it
#define FUNCTION(name, a) int fun_##name() { return a;}
 
FUNCTION(abcd, 12)
FUNCTION(fff, 2)
FUNCTION(kkk, 23)
 
#undef FUNCTION
#define FUNCTION 34
#define OUTPUT(a) cout << #a << '\n'
 
int main()
{
    cout << "abcd: " << fun_abcd() << '\n';
    cout << "fff: " << fun_fff() << '\n';
    cout << "kkk: " << fun_kkk() << '\n';
    cout << FUNCTION << '\n';
    OUTPUT(million);               //note the lack of quotes
}