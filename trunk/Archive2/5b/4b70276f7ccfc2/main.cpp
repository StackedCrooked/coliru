#include <iterator>
#include <memory>
#include <utility>

template<class T>
class any_iterator
  : std::iterator<T, std::forward_iterator_tag>
{
    struct interface;
    using impl_pointer = std::unique_ptr<interface>;
    
    struct interface{
        virtual T& deref() const = 0;
        virtual void inc() = 0;
        virtual impl_pointer copy() const = 0;
        virtual bool eq(interface const&) const = 0;
        virtual ~interface(){}
    };
    template<class It> struct impl
        : interface
    {
        It it;
        
        impl(It i) : it(i){}
        
        T& deref() const override { return *it; }
        void inc() override { ++it; }
        impl_pointer copy() const override { return make_impl(it); }
        bool eq(interface const& other) const override { return it == static_cast<impl const&>(other).it; }
    };
    
public:
    template<class It>
    any_iterator(It it)
      : _impl(make_impl(it)) {}
      
    any_iterator(any_iterator const& other) // yadda yadda, Ro0, I know I know
      : _impl(other._impl->copy()) {}
    
    any_iterator& operator=(any_iterator const& other){
        _impl = other._impl->copy();
        return *this;
    }
          
    any_iterator(any_iterator&&) = default;
    any_iterator& operator=(any_iterator&&) = default;
    ~any_iterator() = default;
    
    // iterator interface
    
    T& operator*() const{ return _impl->deref(); }
    any_iterator& operator++(){ _impl->inc(); return *this; }
    any_iterator operator++(int){ auto self = *this; _impl->inc(); return self; }
    
    bool operator==(any_iterator const& other) const{ return _impl->eq(*other._impl); }
    bool operator!=(any_iterator const& other) const{ return !(*this == other); }

private:
    template<class It>
    static impl_pointer make_impl(It it){ return impl_pointer(new impl<It>{it}); }

    impl_pointer _impl;
};

// test code

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

void f(any_iterator<int> first, any_iterator<int> last){
    for(; first != last; ++first)
        std::cout << *first << " ";
    std::cout << "\n";
}

int main(){
    std::vector<int> v{1,2,3};
    std::deque<int> d{1,2,3};
    std::list<int> l{1,2,3};
    std::forward_list<int> fl{1,2,3};
    
    std::cout << "vector: "; f(v.begin(), v.end());
    std::cout << "deque: "; f(d.begin(), d.end());
    std::cout << "list: "; f(l.begin(), l.end());
    std::cout << "forward_list: "; f(fl.begin(), fl.end());
}