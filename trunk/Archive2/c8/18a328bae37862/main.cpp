#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <list>
#include <set>

struct mesh
{
    using node_t = int;
    using nd_set_t = std::set<node_t>;
    nd_set_t s;
    nd_set_t& nodes() { return s; }
};

template <typename T>
struct unique_owned_item_filter : std::unary_function<T,bool>
{
    bool operator()(const T& item) const
    {
        return true;
    }

    typedef T item_type;
};

template <typename mesh_type, typename rule_type>
void create_double_nodes(mesh_type& mesh, const rule_type& rule)
{
    typename mesh_type::nd_set_t::const_iterator it_first( mesh.nodes().begin());
    while (it_first != mesh.nodes().end())
    {
        if (rule(*it_first))
        {
        }
        it_first++;
    }
}

template <typename mesh_type>
void read_nodes(mesh_type& mesh)
{
   typedef typename mesh_type::node_t nd_t;
   create_double_nodes(mesh, unique_owned_item_filter<nd_t>());
}

int main()
{
    mesh m;
    read_nodes(m);
}
