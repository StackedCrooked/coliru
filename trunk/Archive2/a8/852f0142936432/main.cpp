#include <functional>
#include <string>
#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

class foo
{
    public:
        bool should_delete() { return true; }
};

int main()
{
    using namespace std::placeholders;
    
    boost::ptr_vector<foo> v;
    v.erase_if(std::bind(&foo::should_delete, _1));
}