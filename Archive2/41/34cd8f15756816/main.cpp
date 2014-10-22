template<class T>
class A {
protected:
    int x;
};

template<class T>
class B : public A<T> {
public:
    B() { any_random_garbage_or_maybe_just_a_typo  = 3; }
    
    int any_random_garbage_or_maybe_just_a_typo;
};


int main(int argc, char** argv) {
    B<int> b;
    return 0;
}