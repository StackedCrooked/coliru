#include <iostream>
#include <string>
#include <vector>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/iterator_range.hpp>

template<typename Value>
class pointer_iter 
    : public boost::iterator_adaptor<
        pointer_iter<Value>,
        Value*,
        Value,
        boost::random_access_traversal_tag,
        Value* 
    >
{
public:
    pointer_iter()
        : pointer_iter::iterator_adaptor_(0) {}

    pointer_iter(Value* ptr)
        : pointer_iter::iterator_adaptor_(ptr) {}
private:
    friend class boost::iterator_core_access;

    typename pointer_iter::reference dereference() const {
        return this->base_reference();
    }
};

// TODO add const overload
template<typename Container> 
boost::iterator_range<pointer_iter<typename Container::value_type>>
make_ptr_range(Container& container) {
    typedef pointer_iter<typename Container::value_type> ptr_type;
    return boost::make_iterator_range(
        ptr_type(&*container.begin()), ptr_type(&*container.end()));
}


int main() {
    std::vector<std::pair<int, std::string>> vec{{1, "SO"}, {2, "rocks"}};

    for(auto ptr : make_ptr_range(vec)) {
        std::cout << ptr->second << std::endl;
    }
} 
