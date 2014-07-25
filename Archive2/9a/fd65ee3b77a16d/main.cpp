#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>

using component_id_t = size_t;

template <typename T>
component_id_t constexpr component_id();

template <typename Derived>
struct component_concept
{
    virtual ~component_concept() = default;
    
    static component_id_t constexpr const id_{ component_id<Derived>() };
};


struct position : component_concept<position>
{ float x{}, y{}; };

template <>
component_id_t constexpr component_id<position>()
{ return 1; }


struct velocity : component_concept<velocity>
{ float x{}, y{}; };

template <>
component_id_t constexpr component_id<velocity>()
{ return 1 << 1; }

int main()
{
    position const p;
    velocity const v;
}
