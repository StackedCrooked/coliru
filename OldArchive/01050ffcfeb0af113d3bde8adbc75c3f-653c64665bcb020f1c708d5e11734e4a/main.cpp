#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
#include <stdio.h>

template<class A, class B, B(A) Call>
F<B> fmap(Call call, F<A> fa){ F<B> fb; for(auto&& a : fa){ fb.push_back(call(a)) } return fb; }

struct A
{
};

struct callable
{
    void operator()(A a)
    {
        std::cout << "Callable" << std::endl;
    }
};


int main (int argc, char* argv[])
{
    callable cl;
   F<A,callable, callable>(cl, 
        

    
   return 0;
}