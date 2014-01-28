#include <iostream>

using namespace std;

struct X
{
    int x;
    int y;
};

int main()
{
    X x = {1,2};
    cout << x.x << ", " << x.y << endl;
}