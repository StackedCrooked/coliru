template <typename T>
class foo {
    template <typename U>
    foo& operator=(foo<U> const&);
};
template <typename T, typename U> void f(foo<T>, foo<U>);

template <typename T>
template <typename U>
foo<T>& foo<T>::operator=(foo<U> const& that) {
    f(*this, that);
}

int main() {}