void f() {
    throw 5;
}

void g() noexcept {
    f();
}

int main() {
    try {
        g();
    } catch (int) {}
}
