#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <typeinfo>


template <typename T> void info(const std::vector<T>& vec)
{
    std::cout<<"vector size"<<vec.size()<<" Value of types"<<typeid(T).name()<<" Capacity is "<<vec.capacity()<<"\n";
    if(!vec.empty())
        std::cout<<"buffer starts at address"<<std::addressof(vec.front())<<"\n-------------\n";
}

struct A
{
    int i;
    double d[20];
    char ptr;
};

int print_data(A struct_pointer)
{
    std::cout<<struct_pointer.i<<"\n"<<struct_pointer.d<<"\n"<<struct_pointer.ptr<<"\n";
    return 0;
}

int main()
{
    A a;
    A a1 {50, {2.6,5.0},'a'};
    A a2 {};
    print_data(a);
    print_data(a1);
    print_data(a2);
    //print_data(a3);
    //int w {};//default initialization
    //int x(30);
    //int y= 40;
    //int z{30};
    //string v {};
    /*std::vector<int> seq;
    seq.reserve(600);
    for(int i=0;i<1000;++i)
    {
        if(i%100==0) info(seq);
        seq.push_back(std::rand());
    }*/
    //std::cout<<w<<"\n"<<x<<"\n"<<y<<"\n"<<z<<"\n"<<v;
}