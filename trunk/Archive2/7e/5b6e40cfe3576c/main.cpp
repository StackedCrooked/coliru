    #include <type_traits>

template <typename T>
void myFunction(int b, typename std::enable_if<std::is_same<int B, T>::value, void>::type* = nullptr) {
    }
    int main() {
    myFunction(42);
    return 0;
    }