#include <type_traits>
#include <iostream>
#include <cassert>

using namespace std;


class NonCopyable
{
    NonCopyable(NonCopyable const&) = delete;
};

template <typename T>
class Wrapper
{
    //Wrapper(const Wrapper&, typename enable_if<is_copy_constructible<T>::value, int>::type i = 0) {}
    Wrapper(const Wrapper&){}
};



 
int main()
{
  cout << is_copy_constructible<Wrapper<int>>::value << endl;
  //cout << is_copy_constructible<Wrapper<NonCopyable>>::value << endl;
}