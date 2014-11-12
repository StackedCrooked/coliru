#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

template<typename T>
T copy(const T& arg)
{
    return arg;
}

template<typename T>
void test(T&& arg)
{
    typename remove_reference<T>::type val(move(arg));
    cerr << "test called with: " << val << endl;
}


int main(int argc, char** argv)
{  
    string ttt = "Test string";
    
    //I want the next line to compile:
    //test<string>(ttt);

    //but this will generate the following error message:
    //main.cpp:31:5: error: no matching function for call to 'test'
    //    test<string>(ttt);
    //    ^~~~~~~~~~~~
    //main.cpp:17:6: note: candidate function [with T = std::basic_string<char>] not viable: no known conversion from 'string' (aka 'basic_string<char>') to 'std::basic_string<char> &&' for 1st argument
    //void test(T&& arg)
    //    ^
    //1 error generated.

    //to fix it, this walkaround can be used:
    test<string>(copy(ttt));
    cerr << (ttt.length() ? "Object copied" : "Object moved") << endl;

    //1st question:
    //why the compiler can not implicitly create a copy of an object 
    //if lvalue is passed to a function requiring rvalue reference?

    //and if we want to explicitly specify that move semantics should be used
    //we already have this mechanism: 
    test<string>(move(ttt));
    cerr << (ttt.length() ? "Object copied" : "Object moved") << endl;
    
    //2nd question:
    //am I missing something and stl has already defined way of cloning copy-constructable objects
    //the same way I have done with "copy" templated function

    return 0;
}
