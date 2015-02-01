struct Blob {
    static constexpr float a = 10.0f;
};

int main() {
    Blob b;
    auto c = b.a;
}