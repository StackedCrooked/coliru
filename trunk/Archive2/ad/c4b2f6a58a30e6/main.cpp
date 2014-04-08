#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

struct foo
{
    bool operator ==(foo const &rhs) const
    { return this == &rhs; }
};


// bring this in and the member function out for things to work
//bool operator ==(foo const &lhs, foo const &rhs)
//{ return &lhs == &rhs; }

int main() {
	std::vector<std::reference_wrapper<foo>> v;
    foo f;
    std::find(v.begin(), v.end(), std::ref(f)); // looks for operator==
    
    std::cout << "done" << std::endl;
}