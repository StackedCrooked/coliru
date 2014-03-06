#include <type_traits>
#include <iterator>
#include <iostream>

template<typename Var, typename Cont>
struct WithExisting {
public:
    typedef typename std::remove_reference<Cont>::type cont_noref;
    
private: // note that we have to pass "cont_noref&" to declval, because std::begin doesn't work on rvalue arrays
    typedef decltype(std::begin(std::declval<cont_noref&>())) cont_iterator;
    typedef cont_iterator const_cont_iterator;
  
    struct Iterator {
        typedef Var &reference;
        typedef Var value_type;
        
    public:
        Iterator(Var &var, cont_iterator contIterator):var(var), contIterator(contIterator) { }
        
    public:
        Iterator operator++(int) {
            return Iterator(var, contIterator++);
        }
        
        Iterator &operator++() {
            ++contIterator;
            return *this;
        }
        
        Iterator operator--(int) {
            return Iterator(var, contIterator++);   
        }
        
        Iterator &operator--() {
            --contIterator;   
            return *this;
        }
        
        Var &operator*() const {
            var = *contIterator;
            return var;
        }
        
        friend bool operator==(Iterator a, Iterator b) {
            return a.contIterator == b.contIterator;   
        }
        friend bool operator!=(Iterator a, Iterator b) {
            return !(a == b);   
        }  
        
    private:
        Var &var;
        cont_iterator contIterator;
    };
    
public:
    typedef Iterator iterator;
    typedef Iterator const_iterator;
    
public:
    WithExisting(Var &var, Cont &&cont):var(var), cont(std::forward<Cont>(cont)) { }

    iterator begin() {
        return iterator(var, std::begin(cont));   
    }

    iterator end() {
        return iterator(var, std::end(cont));
    }
    
public:
    Var &var;
    Cont &&cont;
};

template<typename Var, typename Cont>
WithExisting<Var, Cont> with_existing(Var &var, Cont &&cont) {
    return WithExisting<Var, Cont>(var, std::forward<Cont>(cont));
}

int main() {
    int n;
    int a[] = { 1, 2, 3, 4, 5 };
    for(auto &&n : with_existing(n, a)) {
        std::cout << "n is " << n << std::endl;
        n++;   
    }
    std::cout << "n is " << n; // must output "n is 6"
}
