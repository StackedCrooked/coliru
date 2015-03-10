struct Foo {
    using Bar = int;
};

template<class...>
using Foo_t = Foo;

template<class T>
void f(){
    Foo_t<T>::Bar b;
}

int main(){
    f<int>();
}