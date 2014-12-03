#include<iostream>
#include<array>

using namespace std;

inline namespace
{
    template<typename type>
    struct tmp
    {
        tmp() {}
        tmp(const tmp &) = default;
        tmp(const type & arg) : tmp(*(const tmp*)arg) {}

        && operator type() && {return static_cast<type&&>(d);}

        ~tmp () { cout << "tmp destructor" << endl; }

        type d;

    };
}

tmp<tmp<int [4]>> Func() // used 'tmp<int [4]>' instead of array to track object destruction (but normally it should be an native array type
{
    return tmp<tmp<int [4]>>();
}
    
int main()
{
    tmp<int [4]> &&tmp1 = Func();
    
    cout << "Here" << endl;
    
    return 0;
}