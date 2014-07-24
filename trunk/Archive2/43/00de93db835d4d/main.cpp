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
    component_concept()
        : id_{ component_id<Derived>() }
    { std::cout << "created component with id: " << id_ << std::endl; }
    virtual ~component_concept() = default;
    
    component_id_t const id_;
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
