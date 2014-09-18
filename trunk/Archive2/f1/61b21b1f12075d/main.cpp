template <typename X>
class Outer {

    //template<typename T>
    class Inner {

    };

    //template<typename T>
    friend Outer foo();

};

template<typename X>//, typename T>
Outer<X> foo() {
    //typename Outer<X>::template Inner<T> inner;
    typename Outer<X>::Inner inner;
}

int main()
{
    auto a = foo<int, int>();
    (void)a;
}
