#include <vector>

class A {
public:
    std::vector<int> vec;
};

template <typename T> class B : public A {  };

template <typename T> class C : public B<T> {
public:
    using A::vec;
    
    int test() {
        return A::vec[1];      // OK
    }

    int test2() {
        return A::vec.size();  // error: 'class A' has no member named 'size'
    }
};

int main() {
    C<double> c;
    return 0;
}