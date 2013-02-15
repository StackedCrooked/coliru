struct foo;

int test(foo);

struct foo {
    int x;
};

int test(foo f) {
    return f.x;
}

int main() {
    foo f;
    test(f);
}