#include <iostream>

using namespace std;

// tags
struct tag1{}; 
struct tag2{}; 

// the compliant types, all should typedef tag_type
struct my_type1
{
    using tag_type = tag1;
};
struct my_type2
{
    using tag_type = tag2;
};

// static dispatch via tagging
template <typename T>
void f(T) 
{
    cout << "In void f<typename T>(T)" << endl;

    // why can I call f_helper without forward definition?!?        
    ::f_helper(typename T::tag_type{}); 
}

int main()
{
    my_type1 type1;
    my_type2 type2;

    // how does f below knows about f_helper ?!?!
    // even after instantiation f_helper shouldn't be visible!

    f(type1); 
    f(type2);
}

// helper functions
void f_helper(tag1) 
{
    cout << "f called with my_type1" << endl;
}
void f_helper(tag2)
{
    cout << "f called with my_type2" << endl;
}