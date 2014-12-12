#include <iterator>
#include <type_traits>
#include <cassert>

template<class C>
class index_iterator {
    C* container;
    std::size_t index;
public:
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef decltype((*container)[0]) reference;
    typedef decltype(&((*container)[0])) pointer;
    typedef typename std::remove_reference<reference>::type value_type;
    typedef std::random_access_iterator_tag iterator_category;
    
    index_iterator(): container(nullptr), index(0) {}
    index_iterator(C& container_, int index_) : container(&container_), index(index_) {}
    ~index_iterator()=default;
    index_iterator(const index_iterator&)=default;
    index_iterator& operator=(const index_iterator&)=default;
    
    reference operator*() const {assert(index<container->size()); return (*container)[index];}
    pointer operator->() const {assert(index<container->size()); return (*&container)[index];}
    reference operator[](size_type o) const {assert(index+o<container->size()); return (*container)[index+o];}
    
    index_iterator& operator++() {assert(index<container->size()); ++index; return *this;}
    index_iterator operator++(int) {assert(index<container->size()); return index_iterator(*container,index++);}
    index_iterator& operator+=(size_type o) {assert(index+o<=container->size()); index+=o; return *this;}
    friend index_iterator operator+(index_iterator it, size_type o) {return it+=o;}
    friend index_iterator operator+(size_type o, index_iterator it) {return it+=o;}
    index_iterator& operator--() {assert(index<container->size()); --index; return *this;}
    index_iterator operator--(int) {assert(index<container->size()); return index_iterator(*container,index--);}
    index_iterator& operator-=(size_type o) {assert(index>=o); index-=o; return *this;} 
    friend index_iterator operator-(index_iterator it, size_type o) {return it-=o;}
    friend difference_type operator-(index_iterator lhs, index_iterator rhs) {assert(lhs.container==rhs.container); return lhs.index-rhs.index;}    
    
    friend bool operator==(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index==rhs.index;}
    friend bool operator!=(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index!=rhs.index;}
    friend bool operator<(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index<=rhs.index;}
    friend bool operator<=(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index<=rhs.index;}
    friend bool operator>=(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index>=rhs.index;}
    friend bool operator>(const index_iterator&lhs, const index_iterator&rhs){assert(lhs.container==rhs.container); return lhs.index>rhs.index;}    
};

template<class C>
class index_iteratable_wrapper {
    C& container;
public:
    typedef index_iterator<C> iterator;
    typedef index_iterator<const C> const_iterator;
    
    index_iteratable_wrapper(C& container_): container(container_) {}
    iterator begin() {return iterator(container, 0);}
    const_iterator cbegin() {return const_iterator(container, 0);}
    iterator end() {return iterator(container, container.size());}
    const_iterator cend() {return const_iterator(container, container.size());}
};
template<class C>
index_iteratable_wrapper<typename std::remove_reference<C>::type> make_iterable(C&& c) {return index_iteratable_wrapper<typename std::remove_reference<C>::type>(c);}





#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    std::vector<int> mc = {0, 1};
    int i=1; for (auto & e : make_iterable(mc)) { e = i++; }
    auto span = make_iterable(mc);
    for (auto e=span.begin(); e!=span.end(); ++e) { cout << (*e) << endl; }  
    int sum = std::accumulate(span.begin(), span.end(), 0);
    int prod = std::accumulate(span.begin(), span.end(), 1, [](int a, int b) {return a*b;});
}