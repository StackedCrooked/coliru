#include <boost/range/any_range.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/type_traits.hpp>
#include <memory>
#include <vector>

struct IFooBar {
    virtual void func() = 0;
};

typedef boost::any_range<IFooBar,
                         boost::random_access_traversal_tag,
                         const IFooBar&,
                         std::ptrdiff_t> FooBarRange;

void func( const FooBarRange& range ) {
}

int main() {
    std::vector<std::unique_ptr<IFooBar>> vec;
    func( vec | boost::adaptors::indirected );

    return 0;
}