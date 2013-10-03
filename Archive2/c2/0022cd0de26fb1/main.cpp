#include <iostream>
#include <utility>

using namespace std;

class Test
{
public:
    Test(int x, int y)
    {
        cout << "(" << x << ", " << y << ")" << endl;   
    }
};

int main()
{
    int x { 3 };
    int y { -3 };
    
    Test pt { x, y };
    
    return 0;
}