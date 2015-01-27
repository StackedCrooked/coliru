template<class T> struct A {
    struct B {};
};
template<> struct A<int> {
    struct B {};
};

class C {
    template<class T> friend struct A<T>::B;
};	
