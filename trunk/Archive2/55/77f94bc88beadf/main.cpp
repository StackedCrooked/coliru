template<typename T>
class A{
public:
A(T a): a(a){}

template< typename V> V foo(){
    return this->a;
}

private:
T a;
};

template<typename T>
class B{
public:
B( A<T> a): a(a){}

template<typename V>V foo2(){
     return this->a.foo<V>();
}

private:
A<T> a;
};

int
main()
{

    A<int> a(5);
    double  aTest = a.foo<double>();
    B<int> b(a);
    double c = b.foo2< double >();
}