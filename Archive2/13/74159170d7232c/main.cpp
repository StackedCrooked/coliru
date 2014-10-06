#include <random>
#include <type_traits>
#include <cassert>
#include <functional>

template<typename T, typename> class random_generator;

template<typename T, typename A>
class random_iterator {
public:
    using value_type = T;
    using pointer = T*;
    using reference = T;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;    
    random_iterator(random_generator<T,A>& dist, int index) : dist(&dist), index(index), prev(dist()) {}
    random_iterator(const random_iterator& rhs) : dist(rhs.dist), index(rhs.index), prev(rhs.prev) {}
    random_iterator& operator=(const random_iterator&rhs) {dist=rhs.dist; index=rhs.index; prev=rhs.prev; return *this;}
    reference operator*() const {return prev;}
    random_iterator& operator++() {prev=(*dist)();++index; return *this;}
    random_iterator operator++(int) {random_iterator t(*this); ++*this; return t;}    
    friend bool operator==(const random_iterator&lhs, const random_iterator&rhs) {assert(lhs.dist==rhs.dist); return lhs.index==rhs.index;}
    friend bool operator!=(const random_iterator&lhs, const random_iterator&rhs) {assert(lhs.dist==rhs.dist); return lhs.index!=rhs.index;} 
private:
    random_generator<T,A>* dist;
    difference_type index;
    value_type prev;
};

template<typename T,
         typename A= typename std::enable_if<std::is_arithmetic<T>::value>::type>
class random_generator {
    using distribution_type = typename std::conditional<
            std::is_integral<T>::value,
            typename std::uniform_int_distribution<T>,
            typename std::uniform_real_distribution<T>
        >::type;

    std::default_random_engine engine;
    distribution_type distribution;

public:
    auto operator()() -> decltype(distribution(engine)) {
        return distribution(engine);
    }
    random_iterator<T,A> begin() {return {*this, 0};}
    random_iterator<T,A> end(int c) {return {*this, c};}
};

#include <iostream>
#include <list>
#include <iterator>
int main() {
    random_generator<double> gen;
    auto l = std::list<double>(gen.begin(), gen.end(10));
    std::copy(l.begin(), l.end(), std::ostream_iterator<double>(std::cout, ", "));
}