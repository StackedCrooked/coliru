#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

template<class T>
void func(std::initializer_list<T> a_args)
{
    if (a_args.begin() != a_args.end())
    {
        auto last = prev(a_args.end());
        copy(a_args.begin(), last, ostream_iterator<int>(cout, ","));
        cout << *last;
    }
    cout << endl;
}

template<class T, class ...Args>
struct first_of
{
    typedef T type;
};

template<class ...Args>
initializer_list<typename first_of<Args...>::type> foo(Args&&... args)
{
    return { forward<Args>(args)... };
}

int main()
{
    func({1,2,3});
    auto x = foo(1,2,3);
    func(x); //this should be the same as func({1,2,3}) but not.
}
