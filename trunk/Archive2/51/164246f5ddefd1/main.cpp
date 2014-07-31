#include <iostream>
#include <unordered_map>
#include <functional>
#include <iterator>

template<class parent_map, class function_type>
class functional_map
{
public:
    using key_type = typename parent_map::key_type;
    using parent_mapped_type = typename parent_map::mapped_type;
    using mapped_type = decltype(std::declval<function_type>()(std::declval<parent_mapped_type>()));
    using size_type = typename parent_map::key_type;
    using difference_type = typename parent_map::key_type;
    
    class const_iterator {
        friend functional_map;
    public:
        using value_type = mapped_type;
        using reference_type = mapped_type;
        using pointer_type = mapped_type*;
        using size_type = typename functional_map::size_type;
        using iterator_category = std::input_iterator_tag;
        
        static_assert(std::is_same<reference_type,std::string>::value,"WHAT THE");
    
        const_iterator() = default;
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
        
        reference_type operator*() {return parent->func(*it);}
        //rvalue_ptr<reference_type> operator->() {return rvalue_ptr<reference_type>(parent->func(*it));}
        
        const_iterator& operator++() {++it; return *this;}
        const_iterator operator++(int) {const_iterator t(*this); ++it; return t;}
        const_iterator& operator--() {--it; return *this;}
        const_iterator operator--(int) {const_iterator t(*this); --it; return t;}
        
        friend bool operator==(const const_iterator&lhs, const const_iterator&rhs)
        {assert(lhs.parent == rhs.parent); return lhs.it == rhs.it;}
        friend bool operator!=(const const_iterator&lhs, const const_iterator&rhs)
        {assert(lhs.parent == rhs.parent); return lhs.it != rhs.it;}
    private:
        const_iterator(typename parent_map::const_iterator it, const functional_map* parent) :it(it), parent(parent) {}
        typename parent_map::const_iterator it;
        const functional_map* parent;
    };
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    functional_map(const parent_map& parent, function_type func) :parent(&parent), func(std::move(func)) {}
    
    const_iterator begin() const noexcept {return const_iterator(parent->begin(), this);}
    const_iterator end() const noexcept {return const_iterator(parent->end(), this);}
    const_reverse_iterator rbegin() const noexcept {return const_reverse_iterator(const_iterator(parent->end(), this));}
    const_reverse_iterator rend() const noexcept {return const_reverse_iterator(const_iterator(parent->begin(), this));}
    
    bool empty() const noexcept {return parent->empty();}
    bool size() const noexcept {return parent->size();}
    
    mapped_type operator[](const key_type& k) {return func(parent->at(k));}
    mapped_type at(const key_type& k) const {return func(parent->at(k));}
    const_iterator find(const key_type& k) const {return const_iterator(parent->find(k), this);}
    size_type count(const key_type& k) const {return parent->count(k);}
    std::pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
        auto src = parent->equal_range(k);
        return std::pair<const_iterator,const_iterator>(const_iterator(src.first,this), const_iterator(src.second,this));
    }
private:
    const parent_map* parent;
    function_type func;
};

template<class K,class T,class H,class P,class A,class function_type>
auto Map(const std::unordered_map<K,T,H,P,A>& source, function_type func) 
    -> functional_map<std::unordered_map<K,T,H,P,A>,function_type>
{return functional_map<std::unordered_map<K,T,H,P,A>,function_type>(source, std::move(func));}

#include <string>

int main()
{
    std::unordered_map<int, char> source = {
        {1, 'a'},
        {2, 'b'},
        {3, 'c'},
    };
    auto func = [](char i)->std::string{return std::string(3, i);};
    auto mapping = Map(source, func);
    std::cout << mapping[2];
    return 0;
}