template <typename T> T& copy(T&& t) { return t; }

int main() {
    copy(1) = 2;
}
