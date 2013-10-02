template <class T>
struct A {
    void f22(){}
    void f11(){}
};

template <class T>
struct B : public A <T> {
    void f1() { A<T>::f11(); }
    void f2() { this->f22(); }   // calling base function - will not compile
};

int main()
{
}