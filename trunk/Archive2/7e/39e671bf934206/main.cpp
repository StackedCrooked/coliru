// nth_element example
#include <iostream>     // std::cout
#include <algorithm>    // std::unth_element, std::random_shuffle
#include <vector>       // std::vector
#include <string>

using namespace std;

struct A
{
    int a;
    string b;  
    A(int a, string b): a(a), b(b)
    {        
    }
    
    A(A&& other): a(other.a), b(other.b)
    {        
    }
};

A&& factory(int a, string c)
{
    return move(A(a,c));
}

int main () {
    A test(factory(2,string("abc")));
    cout<<test.a<<endl;
    cout<<test.b<<endl;
    return 0;
}