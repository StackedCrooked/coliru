#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

class Mine {
public:
    int value;
    Mine(int x, int y) : value(10*x + y) {}
};

vector<int> v{2};
int x{42};
Mine z[] = {{4,2}};

int main()
{
    assert(v[0] == 2);
    //assert(v[1] == 5);
    assert(x == 42);
    assert(z[0].value == 42);
    cout << "** tests passed **" << endl;
}
