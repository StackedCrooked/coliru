template <class T> T&& forward(T& t) noexcept  { return static_cast<T&>(t); }
template <class T> T&& forward(T&& t) noexcept  { return static_cast<T&&>(t); }

template<typename T>
void test(T&& t) { forward<T>(t); }

int main() {
    test(0);
}