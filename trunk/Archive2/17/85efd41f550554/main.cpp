#include <list>
#include <iostream>

using namespace std;

struct D {
    double a[2][2];
};

int main()
{
    std::list<D> mylist;

    D d1 = { 0, 1, 2, 3 };
    D d2 = { 4, 5, 6, 7 };
    
    mylist.push_back(d1);
    mylist.push_back(d2);

    for (auto it : mylist)
    {
        for (int i = 0; i < 2; ++i)
        {
            cout << " {";
            for (int j = 0; j < 2; ++j)
            {
                cout << " " << it.a[i][j];    
            }
            cout << " }";
        }
        cout << endl;
    }
}
