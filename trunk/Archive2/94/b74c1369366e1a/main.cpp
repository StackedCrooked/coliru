#include <boost/bind.hpp>
#include <list>

template <typename F>
struct compare_by_impl {
    compare_by_impl(F f = F()) : _f(f) {}

    template <typename T, typename U>
    bool operator()(T const& a, U const& b) const {
        return _f(a) < _f(b);
    }
  private:
    F _f;
};

template <typename Accessor>
compare_by_impl<Accessor> comparer_by(Accessor f) {
    return compare_by_impl<Accessor>(f);
}

struct MyStruct { int a; int b; };

int main()
{
    std::list<MyStruct> myList;
    //...
    myList.sort(comparer_by(boost::mem_fn(&MyStruct::a)));
}
