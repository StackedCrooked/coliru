void a() { }

void b() {
    return a();
}

void c(void(*f)()) {
    return f();
}

template<typename F>
void d(F f) {
    return f();
}

int main() {
    b();
    c(&a);
    d(&a);
}
