template <typename T>
struct list {

    struct node {
        T t;
    };

    node n;

    template <typename NODE>
    struct iterator_impl {

        NODE* n;

        iterator_impl(NODE *n): n(n){}

        auto& operator * () const {
            return n->t;
        }
    };

    using  iterator = iterator_impl<      node>;
    using citerator = iterator_impl<const node>;

    iterator begin() {
        return iterator(&n);
    }

    citerator begin() const {
        return citerator(&n);
    }

};

#include <type_traits>
#include <iostream>

void foo(const list<int> &a){
    std::cout << *a.begin() << std::endl;
}

int main(){
    list<int> a;
    //std::cout << std::is_const<decltype(*a.begin())>::value << std::endl;
    *a.begin() = 1;
    foo(a);
}
