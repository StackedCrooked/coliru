#include <boost/intrusive/list.hpp>
using namespace boost::intrusive;

struct my_class : list_base_hook<link_mode<auto_unlink> > { };
typedef list<my_class, constant_time_size<false> > my_class_list;

#include <iostream>

int main()
{
    const int MaxElem = 100;

    std::vector<my_class> nodes;
    nodes.reserve(MaxElem*2); // DIMENSIONS!

    //////////////////////////////////////////////
    // He's making a list
    my_class_list list;
    nodes.resize(MaxElem);
    list.insert(list.end(), nodes.begin(), nodes.begin()+MaxElem);

    auto const not_reallocated = nodes.data();

    //////////////////////////////////////////////
    // He's checking it twice
    my_class_list cloned_list;
    cloned_list.clone_from(
            list, 
            [&nodes,not_reallocated](my_class const&v) { 
                nodes.push_back(v); 
                assert(not_reallocated == nodes.data());
                return &nodes.back(); 
            },
            [](my_class*){}
        );

    std::cout << std::boolalpha;
    std::cout << "nodes[0].is_linked()       : " << nodes[0].is_linked()             << std::endl;
    std::cout << "nodes[0].is_linked(): "        << nodes[MaxElem].is_linked()       << std::endl;
    std::cout << "list[0].is_linked()        : " << list.begin()->is_linked()        << std::endl;
    std::cout << "cloned_list[0].is_linked() : " << cloned_list.begin()->is_linked() << std::endl;

    //////////////////////////////////////////////
    // Gonna find out who's naughty or nice:
    auto nit = nodes.begin()+MaxElem;
    auto lit = cloned_list.begin();

    while (nit != nodes.end() && lit != cloned_list.end()) {
        assert(&(*nit++) == &(*lit++)); // this would fail if you didn't `reserve()` the vector up front
    }

    //////////////////////////////////////////////
    // now, if you really want you can do
    cloned_list.clear();
    // let's be very precise:
    nodes.erase(std::remove_if(
                nodes.begin(), nodes.end(), 
                [](my_class const& v) { return !v.is_linked(); }),
            nodes.end());

    assert(nodes.size()==MaxElem);
}
