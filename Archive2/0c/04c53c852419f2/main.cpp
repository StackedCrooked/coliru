#include <array>
#include <iostream>

using namespace std;

typedef struct{
 int i;
 char a;
}mystruct;

int main()
{
    std::array<mystruct, 2> structure = {{}};
    structure[0].i = 69;
    cout << structure[0].i << endl; // Should print 69
    structure = {{}};
    cout << structure[0].i << endl; //Should print 0
}
