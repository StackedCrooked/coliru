

template <typename... Args>
int foo(Args... args) = delete;

template <>
int foo<int, int>(int, int) {
    return 1;    
}

int main() {

}