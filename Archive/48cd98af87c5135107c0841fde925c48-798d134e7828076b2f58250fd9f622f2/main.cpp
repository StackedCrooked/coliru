#include <iterator>
#include <cassert>

class Foo {
private:
    int a,b,c,d;
    char bar;
    double m,n;
    
    struct iterator { 
        typedef int value_type;
        typedef int& reference_type;
        typedef int* pointer_type;
        typedef int difference_type;
        typedef std::output_iterator_tag iterator_category;
        
        iterator& operator++() {++index; return *this;}
        iterator operator++(int) {return iterator(parent, index++);}
        reference_type operator*() const {
            switch(index) {
            case 0: current=parent->c; break;
            case 1: current=parent->b; break;
            case 2: current=parent->d; break;
            case 3: current=parent->m; break;
            case 4: current=parent->bar; break;
            case 5: current=parent->a; break;
            case 6: current=parent->n; break;
            default: assert(!"INVALID ITERATOR");
            }
            return current;
        }
        friend void swap(iterator& lhs, iterator& rhs) {
            std::swap(lhs.parent, rhs.parent);
            std::swap(lhs.index, rhs.index);
        }
        friend bool operator==(const iterator& lhs, const iterator& rhs)
        {return lhs.parent==rhs.parent && lhs.index==rhs.index;}
        friend bool operator!=(const iterator& lhs, const iterator& rhs)
        {return lhs.parent!=rhs.parent || lhs.index!=rhs.index;}
    private: 
        friend Foo;
        explicit iterator(Foo* container, int i=7) :parent(container), index(i) {}
        Foo* parent;
        int index;
        mutable int current;
    };
public:
    iterator begin() {return iterator(this, 0);}
    iterator end() {return iterator(this);}
    //constructors here
    Foo() :a(0), b(1), c(2), d(3), bar('a'), m(4.4), n(5.5) {}
};

#include <iostream>

int main() {
    Foo foo;
    for(auto& f : foo) {
        std::cout << f << ' ';
    }
}
