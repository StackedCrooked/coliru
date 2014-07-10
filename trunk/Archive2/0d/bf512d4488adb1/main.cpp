#include <vector>
#include <iostream>

#include <boost/iterator/iterator_facade.hpp>

struct const_foo_iterator : boost::iterator_facade<const_foo_iterator,
                                                    unsigned char const,
                                                    boost::random_access_traversal_tag>
{
  const_foo_iterator() : iter() {}
  const_foo_iterator(unsigned char const *iter) : iter(iter) {}
private:
    friend class boost::iterator_core_access;

    void increment() { ++iter; }
    bool equal(const_foo_iterator const& other) const
    {
        return this->iter == other.iter;
    }
    unsigned char const& dereference() const { return *iter; }
    unsigned char const* iter;
};

class foo {
    unsigned char* value;
    int length;

    const_foo_iterator begin();
    const_foo_iterator end();
};

const_foo_iterator foo::begin() {
    return value;
}

const_foo_iterator foo::end() {
    return value + length;
}

#include <iterator>
#include <type_traits>

int main()
{
    static_assert(std::is_same<std::iterator_traits<const_foo_iterator>::value_type,
                               unsigned char>::value, "value_type");
    static_assert(std::is_same<std::iterator_traits<const_foo_iterator>::pointer,
                               unsigned char const *>::value, "pointer");
    static_assert(std::is_same<std::iterator_traits<const_foo_iterator>::iterator_category,
                               std::random_access_iterator_tag>::value, "iterator_category");
}
