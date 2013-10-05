#include <iostream>

template <class T>
class MyCont
{
    public:
        void SomeFunc();
        T* list;
};

template <class T>
struct MyCont< MyCont<T> > : MyCont<T>
{
        void SomeFunc();
};

template <typename T>
void MyCont< MyCont<T> >::SomeFunc()
{
    std::cout<<"in altered function"<<std::endl;
    //...
}

template <class T>
void MyCont<T>::SomeFunc()
{
    std::cout<<"in function"<<std::endl;
    //...
}

int main()
{
    MyCont<int> y;
    y.SomeFunc();
    MyCont< MyCont<int> > x;
    x.SomeFunc();
}
