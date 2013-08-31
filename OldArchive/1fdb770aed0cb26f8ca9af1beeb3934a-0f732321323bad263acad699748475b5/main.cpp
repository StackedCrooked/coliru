struct foo {
    ctor a(bar);
    ctor b(qux);
};

void emplace(lazy foo thing) {
    ::new(ptr) thing;
}

int main() {
    emplace(foo.a(some_bar));
    emplace(foo.b(some_qux));
}