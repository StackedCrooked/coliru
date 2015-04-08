
void foo(int) {}
void foo(long double) {}
void foo(void*) {}

template<class T>
?????? get_foo_ptr(T v) {
    ???????
}

int main() {
    void(*this_foo)(int) = get_foo_ptr('c');
    this_foo('c');
}