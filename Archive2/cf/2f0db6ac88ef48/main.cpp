#include <iostream>

using std::cout;
using std::endl;

template<bool b, typename T> struct cond { };

template<typename first, typename... params> struct q;

template<typename first> struct q<first>
{
    q()
    {
        cout<<"x"<<endl;
    }
};

template<typename T> struct q<cond<true, T>>
{
    q()
    {
        cout<<"x"<<endl;
    }
};

template<typename T> struct q<cond<false, T>> { };

template<typename first, typename... params> 
struct q
{
    q()
    {
        cout<<"x";
        q <params...> ();
    }
};

int main()
{
    q<int, int> ();
    q<int, int, cond<true, bool>>();
    q<int, int, cond<false, bool>>();
}