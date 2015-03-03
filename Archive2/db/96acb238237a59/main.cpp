int f(void (*(int*, void (*)(long), int, long)) (int*, void (*)(long), int, long*));

#include <iostream>

template<typename T>
void print_type();

template<>
void print_type<void>() {
    std::cout << "void";
}

template<>
void print_type<int>() {
    std::cout << "int";
}

template<>
void print_type<long>() {
    std::cout << "long";
}

template<typename T>
struct decompose
{
    void print() { print_type<T>(); }
};

template<typename T>
struct decompose<T*>
{
    void print() { std::cout << "pointer to "; decompose<T>{}.print(); }
};

template<typename R, typename... Params>
struct decompose<R(Params...)>
{
    void print() {
        std::cout << "{function taking (";
        int _[] { 0, (decompose<Params>{}.print(), std::cout << ", ", 0)... };
        (void)_;
        std::cout << ") and returning ";
        decompose<R>{}.print();
        std::cout << "}";
    }
};

int main()
{
    decompose<decltype(f)>{}.print();
}