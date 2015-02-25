struct T { };

int main() {
    T f();
    return sizeof(decltype(f()));
}