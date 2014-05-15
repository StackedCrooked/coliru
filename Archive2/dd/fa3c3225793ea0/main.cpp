#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/dynamic_bitset.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct A
{
    int a_val;
    A() : a_val(0) {}
    A(int a) : a_val(a) {}

    friend std::ostream& operator<<(std::ostream &output, A &a_obj)
    {
        output << a_obj.a_val;
        return output;
    }
};

template <typename tree_type_t>
struct simple_tree_t
{
    simple_tree_t() {}
    simple_tree_t( tree_type_t t_obj):tree_data(t_obj) {}
    tree_type_t tree_data;

    std::vector < std::shared_ptr < tree_type_t > > sub_tree;

    typedef typename std::vector < std::shared_ptr < tree_type_t > >::iterator sub_tree_iterator;

    sub_tree_iterator sub_tree_begin() { return sub_tree.begin(); }
    sub_tree_iterator sub_tree_end() { return sub_tree.end(); }

    friend std::ostream& operator<<(std::ostream &output, simple_tree_t &tree)
    {
        output << tree.tree_data;
        std::for_each ( tree.sub_tree_begin(), 
                        tree.sub_tree_end(), 
                        ([&](const std::shared_ptr < A > f){
                            output << *f;
                            }) );
        return output;
    }
};

BOOST_FUSION_ADAPT_STRUCT ( A,
                                (int , a_val) )

BOOST_FUSION_ADAPT_TPL_STRUCT ( (tree_type_t),
                                (simple_tree_t) (tree_type_t),
                                (tree_type_t, tree_data)
                                (typename std::vector < std::shared_ptr < tree_type_t > > , sub_tree) )

int main(void)
{
    simple_tree_t<A> t_i, t_o;

    t_i.tree_data = A(10);
    t_i.sub_tree.push_back(std::make_shared<A>(A(20)));
    t_i.sub_tree.push_back(std::make_shared<A>(A(30)));

    std::cout << t_i << std::endl;

    return 0;
}
