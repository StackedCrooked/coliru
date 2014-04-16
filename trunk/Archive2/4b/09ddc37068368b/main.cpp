#include <boost/iterator/iterator_facade.hpp>

struct my_obj
{
    my_obj(std::string v) :value(v) {}
    std::string value;
};

class my_iterator 
    : public boost::iterator_facade<
        my_iterator,
        my_obj,
        boost::forward_traversal_tag,
        my_obj>   //tell iterator_facade that dereference gives a "my_obj" instead of an "my_obj"
{
public:
    my_obj dereference() const
    {
        return my_obj("HI");
    }
};

int main( int argc, char* argv[])
{
    my_iterator it;
    it->value;
}