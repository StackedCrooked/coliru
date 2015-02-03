struct X {
    X(X const&) = delete;
    X& operator=(X const&) = delete;
};

int main() {
    X x;
}
