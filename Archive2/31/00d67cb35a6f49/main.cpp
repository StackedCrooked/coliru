#include <boost/type_index.hpp>
#include <iostream>

struct A
{
  void foo() {}
};

int main()
{
    std::cout << boost::typeindex::type_id_with_cvr<A&>().pretty_name() << '\n';
    std::cout << boost::typeindex::type_id_with_cvr<decltype(&A::foo)>().pretty_name() << '\n';
}
