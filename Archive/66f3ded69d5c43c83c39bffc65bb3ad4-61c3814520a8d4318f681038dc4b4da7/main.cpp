template <class T>
class Outer {
    Outer();
    void foo();
};

template<class T>
Outer<T>::Outer<T>() {}

// Not working
template <class T>
typename Outer<T>::Inner* Outer<T>::x = 0;

int main() {
    int x;
}