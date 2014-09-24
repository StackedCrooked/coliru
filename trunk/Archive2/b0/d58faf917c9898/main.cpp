struct incomplete;

template<class T>
struct A { T d; };

template <class T>
struct B { };

int main() {
    B<A<incomplete>> a, b;
    a = b;
}