struct Blob {
    static constexpr float a = 10;
};

int main() {
    Blob b;
    auto c = b.a;
}
