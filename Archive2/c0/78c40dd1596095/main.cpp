namespace test {

template <typename Derived>
struct foo;

template <typename X>
struct bar;

namespace detail {

template <typename T, typename U>
void f(foo<T>&, foo<U> const&);

}

template <typename Derived>
struct foo {
public:
    template <typename U>
    foo& operator=(foo<U> const& that);
};

template <typename X>
struct bar : foo<bar<X>> {
private:
    using base_type = foo<bar<X>>;

public:
    using base_type::operator=;
};

namespace detail {

template <typename Derived>
struct foo;

template <typename T, typename U>
void f(foo<T>& adst, foo<U> const& asrc);

template <typename T, typename U>
void f(foo<T>&, foo<U> const&) {}

}

template <typename T>
template <typename U>
foo<T>& foo<T>::operator=(foo<U> const& that) {
    detail::f(*this, that);
    return *this;
}

}

int main() {
    test::bar<struct strawberry> a;
    test::bar<struct caramel> b;
    a = b;
}
