template <typename TT>
struct B;

template <class> struct B_traits;
template<class TT> 
struct B_traits<B<TT>> {
    using tt = TT;
};

template <typename T>
struct A {
   virtual typename B_traits<T>::tt returns_something();
};
template <typename TT>
struct B : A<B<TT>> {
    typedef TT tt;
    virtual tt returns_something() override;
};

int main() {
    B<float> f;
    
}