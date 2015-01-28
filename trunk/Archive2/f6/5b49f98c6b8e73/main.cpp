struct A {
    A(int){}
    A(A&&) = delete;
};

int main() {
    A a = {1};
}