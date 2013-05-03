#include <iostream>
using namespace std;

class ex
{
    private: int i; float j;
    public: ex(int ii =0, float jj =0)
            {
                i = ii; j = jj;
            }
            void print()
            {
                cout << i << " " << j << "\n";
            }
};

int main()
{
    ex e;
    e.print();
    return 0;
}