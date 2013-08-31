#include <string>
#include <iostream>

template <typename T>
struct Foo1{
};

template <template <typename> class P>
struct b {
    template <class, template <typename> class FriendP>
    friend void f(b<FriendP> from){
        std::cout << "here we are" << std::endl;
    }
};

int main()
{
      b<Foo1> bf1i;
      f<int>(bf1i);
} 