#include <iostream>


template<typename T>
struct vector
{};


template<>
struct vector<bool>
{
    [[deprecated( "Please don't use std::vector<bool>" )]]
    vector() = default;    
};

int main()
{
    vector<bool> v;   
}