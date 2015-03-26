#include <vector>
#include <iostream>
using namespace std;

class Base{};

template <typename D, typename B = Base>
class CrtpBase : public B
{
    public:
    int index(size_t ind){return static_cast<D*>(this)->_array[ind];}
};

struct Derived1 : public CrtpBase<Derived1>
{
    vector<int> _array = {1,2,3};
};

struct Derived2 : public CrtpBase<Derived2>
{
    vector<int> _arr = {4,5,6};
    vector<int>& _array = _arr;
};

int main()
{
    Derived1 d1;
    Derived2 d2;
    cout << d1.index(0) << " " << d2.index(0) << endl;
    return 0;
}