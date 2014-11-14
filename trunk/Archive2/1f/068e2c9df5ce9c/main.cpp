#include <boost/range/any_range.hpp>
#include <memory>

template <typename T>
struct container_holder {
    typedef T         value_type;
    typedef T&        reference_type;
    typedef ptrdiff_t difference_type;

    // allow generic "default" constructors
    template <typename> struct typetag {};

    template <typename Container> container_holder(typetag<Container>)
        : _holder(new holder_t<Container>)
    { }

  private:
    struct base_ {
        typedef boost::any_range<value_type, boost::forward_traversal_tag, value_type, difference_type> range;
        virtual range get_range() = 0;
        virtual size_t size() const = 0;
        virtual void append(value_type const&) = 0;
        virtual ~base_() {}
    };
            
    template <typename Impl> struct holder_t : base_ {
        Impl storage;

        virtual typename base_::range get_range() { return boost::make_iterator_range(storage.begin(), storage.end()); }
        virtual size_t size()               const { return storage.size(); }
        virtual void append(value_type const& v)  { storage.insert(storage.end(), v); }
    };
    
    std::unique_ptr<base_> _holder;

  public:
    typedef typename boost::range_iterator<typename base_::range>::type iterator;

    iterator begin() { return _holder->get_range().begin(); }
    iterator end()   { return _holder->get_range().end(); }
    size_t   size()  { return _holder->size(); }
    void append(value_type const& v) { _holder->append(v); }
};

// convenience factory functions
template <typename Container, typename R = container_holder<typename Container::value_type>> 
R make_container_holder(Container* = nullptr) {
    return R(typename R::template typetag<Container>());
}

// demo
#include <iostream>
#include <list>
#include <set>
#include <vector>

template <typename T, typename R = container_holder<T>  >
  R make_vector_holder() { return R(typename R::template typetag<std::vector<T> >()); }
template <typename T, typename R = container_holder<T>  >
  R make_set_holder()    { return R(typename R::template typetag<std::set<T> >()); }
template <typename T, typename R = container_holder<T>  >
  R make_list_holder()   { return R(typename R::template typetag<std::list<T> >()); }

void simple_test(container_holder<int> holder) {
    holder.append(3); holder.append(2); holder.append(1);
    holder.append(3); holder.append(2); holder.append(1);

    for(auto element : holder)
        std::cout << element << " ";
    std::cout << "\n";
}

int main() {
    simple_test(make_vector_holder<int>());
    simple_test(make_list_holder<int>());
    simple_test(make_set_holder<int>());
}
