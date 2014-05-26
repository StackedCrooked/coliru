
#include <vector>

#include <algorithm>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;

template <class T1>
struct OuterStruct
{
    T1 mValue;
    struct InnerStruct
    {
        T1 mValue;
    };
};


template <class T2>
struct InnerStruct_Wrapper
{
    typename OuterStruct<T2>::InnerStruct  mUsingInner;
};


int main(int argc, char* argv[])
{
    InnerStruct_Wrapper<int> wrapper;
    OuterStruct<int>::InnerStruct innerStrct;
    innerStrct.mValue = std::numeric_limits<int>::max();
    wrapper.mUsingInner = innerStrct;
    cout << "Done\n";
    return 0;
}