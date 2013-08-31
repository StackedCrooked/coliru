#include <iterator>
#include <cassert>
#include <vector>

template<class T>
struct maybe_deleted_iterator {      
    typedef int difference_type;
    typedef T value_type;
    typedef T& reference;
    typedef T* pointer;
    typedef std::forward_iterator_tag iterator_category;
    
    maybe_deleted_iterator() 
    :elements(), deleted(), e_iter(), d_iter() 
    {}
    maybe_deleted_iterator(std::vector<T>& e, std::vector<bool>& d, bool begin) 
    :elements(&e), deleted(&d), e_iter(begin?e.begin():e.end()), d_iter(begin?d.begin():d.end()) 
    {
        assert(e.size()==d.size());
        while(e_iter!=elements->end() && d_iter!=deleted->end() && *d_iter) {
            ++e_iter;
            ++d_iter;
        }
        
    }
    maybe_deleted_iterator& operator++() {
        do {
            ++e_iter;
            ++d_iter;
        } while(e_iter!=elements->end() && d_iter!=deleted->end() && *d_iter);
        return *this;
    }
    reference operator*() const {return *e_iter;}
    pointer operator->() const {return &*e_iter;}
    bool operator==(const maybe_deleted_iterator& rhs) 
    {return e_iter==rhs.e_iter;}
    bool operator!=(const maybe_deleted_iterator& rhs) 
    {return e_iter!=rhs.e_iter;}
private:
    std::vector<T>* elements;
    std::vector<bool>* deleted;
    typename std::vector<T>::iterator e_iter;
    std::vector<bool>::iterator d_iter;
};

#include <iostream>

int main() {
    std::vector<int>   element = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    std::vector<bool>  deleted = {1, 0, 0, 1, 1, 0, 1, 0, 1, 1};
    maybe_deleted_iterator<int> it(element, deleted, true);
    maybe_deleted_iterator<int> end(element, deleted, false);
    for(; it!=end; ++it) {
        std::cout << *it << ' ';
    }
}
    
    