#include <boost/intrusive/list.hpp>
using namespace boost::intrusive;

struct my_class : list_base_hook<link_mode<auto_unlink> > { };
typedef list<my_class, constant_time_size<false> > my_class_list;

#include <iostream>

int main()
{
    const int MaxElem = 100;
    std::vector<my_class> nodes(MaxElem);

    //////////////////////////////////////////////
    // He's making a list
    my_class_list list;
    list.insert(list.end(), nodes.begin(), nodes.end());

    //////////////////////////////////////////////
    // He's checking it twice
    my_class_list cloned_list;
    std::vector<my_class> cloned_nodes;
    cloned_nodes.reserve(MaxElem);
    cloned_list.clone_from(
            list, 
            [&cloned_nodes](my_class const&v) { cloned_nodes.push_back(v); return &cloned_nodes.back(); },
            [](my_class*){}
        );

    std::cout << std::boolalpha;
    std::cout << "nodes[0].is_linked()       : " << nodes[0].is_linked()             << std::endl;
    std::cout << "cloned_nodes[0].is_linked(): " << cloned_nodes[0].is_linked()      << std::endl;
    std::cout << "list[0].is_linked()        : " << list.begin()->is_linked()        << std::endl;
    std::cout << "cloned_list[0].is_linked() : " << cloned_list.begin()->is_linked() << std::endl;

    //////////////////////////////////////////////
    // Gonna find out who's naughty or nice:
    auto nit = cloned_nodes.begin();
    auto lit = cloned_list.begin();

    while (nit != cloned_nodes.end() && lit != cloned_list.end()) {
        assert(&(*nit++) == &(*lit++)); // this would fail if you didn't `reserve()` the vector up front
    }

    //////////////////////////////////////////////
    // now, if you really want you can do
    cloned_list.clear();
    // after which the simplest thing to do would be `cloned_nodes.clear()`, but let's be very precise:
    cloned_nodes.erase(std::remove_if(
                cloned_nodes.begin(), cloned_nodes.end(), 
                [](my_class const& v) { return !v.is_linked(); }),
            cloned_nodes.end());
}
