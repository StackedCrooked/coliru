int main() {
    alignas(sizeof(const volatile unsigned long long int)) static thread_local const volatile unsigned long long int foo{0};
}