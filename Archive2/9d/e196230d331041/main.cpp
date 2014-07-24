#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using component_id_t = size_t;

template <typename T>
component_id_t constexpr component_id();


struct some_component
{ /* ... */ };

template <>
component_id_t constexpr component_id<some_component>()
{ return 42; }

int main()
{
    std::cout << component_id<some_component>() << std::endl;
}
