#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;
class service;
class service_impl;
namespace detail {
service_impl* get_impl(service &s);
}

class service_impl
{
public:
    void foo() { cout << "You have just accessed me!" << endl;}
};

class service
{
    friend service_impl* detail::get_impl(service &s);
    
    service_impl impl_;
};

namespace detail {
service_impl* get_impl(service &s);
{
    return &s.impl_;
}
}


int main()
{
    service s;
    service_impl* impl = get_impl(s);
    impl->foo();
    return 0;
}
