#include <cstddef>
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <ios>

template<class Container>
class clearable_back_insert_iterator
: 
    public std::iterator< std::output_iterator_tag, void, void, void, void >
{
private:
    Container* c_;
    
public:    
    using self_t = clearable_back_insert_iterator;    
    using value_type = typename Container::value_type;
    
    clearable_back_insert_iterator(Container& c): c_(&c) {}
    
    operator std::size_t() { return c_->size(); }

    self_t& operator=(value_type const& v)
    {
        std::cout << "push_back \n";
        c_->push_back(v);    
        return *this;
    }
    
    self_t& operator=(std::nullptr_t)
    {
        std::cout << "clear \n";
        c_->clear();
        return *this;
    }
    
    self_t& operator*() { return *this; }
    self_t& operator++() { return *this; }
    self_t& operator++(int) { return *this; }
};

template<class Container>
clearable_back_insert_iterator<Container> clearable_back_inserter(Container& c)
{
    return clearable_back_insert_iterator<Container>(c);    
}

template<class Container>
void print_container(Container const& c)
{
    for (auto it = begin(c); it != end(c); ++it)
        std::cout << *it << ", ";
    std::cout << "\n";
}

template<class InputIt, class OutputIt>
OutputIt copy_if_max1(InputIt first, InputIt last, OutputIt dst)
{
    using T = typename InputIt::value_type;
    auto m = std::numeric_limits<T>::min();
    std::transform(first, last, dst, [&](T const& elem) {
        if (dst == 0) {             // size()
            m = elem;
            dst = elem;             // push_back()
        }
        if (m <= elem) {
            if (m != elem) {
                m = elem;
                dst = nullptr;      // clear()
            }
            dst = elem;             // push_back()
        }
        return dst;        
    });
    return dst;
}    

int main()
{
    auto a = std::vector<int> { 1, 0, 1, 2, 4, 3, 4, 2 };    
    auto b = std::vector<int> { };
    
    copy_if_max1(begin(a), end(a), clearable_back_inserter(b));
    print_container(b); // 4, 4, 
}