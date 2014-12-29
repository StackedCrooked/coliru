#include <bitset>
#include <iostream>

struct Foo { static int get_id() { return 0; } };
struct Bar { static int get_id() { return 1; } };
struct Baz { static int get_id() { return 2; } };

const unsigned int components_count = 3;

#ifdef FIXED

    template<typename FilterComponent1, typename FilterComponent2, typename ...FilterComponents>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b);
    
    template<typename FilterComponent>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b);
    
    template<typename FilterComponent1, typename FilterComponent2, typename ...FilterComponents>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b)
    {
        b.set(FilterComponent1::get_id());
        return component_impl<FilterComponent2, FilterComponents...>(b);
    }
    
    template<typename FilterComponent>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b)
    {
        b.set(FilterComponent::get_id());
        return b;
    }

#else

    template<typename FilterComponent, typename ...FilterComponents>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b);
    
    template<typename FilterComponent>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b);
    
    template<typename FilterComponent, typename ...FilterComponents>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b)
    {
        b.set(FilterComponent::get_id());
        return component_impl<FilterComponents...>(b);
    }
    
    template<typename FilterComponent>
    std::bitset<components_count> component_impl(std::bitset<components_count> &b)
    {
        b.set(FilterComponent::get_id());
        return b;
    }

#endif

template<typename ...FilterComponents>
std::bitset<components_count> component_mask()
{
    std::bitset<components_count> b;
    component_impl<FilterComponents...>(b);
    return b;
}

int main()
{
    std::cout << component_mask<Foo,Bar,Baz>() << '\n';
}
