
class A{};

template <class T>
class B {
    friend T;    
};

B<A> b;

int main() {
return 0;
}