struct F {};

struct Myclass {
    Myclass(F f) : f(f) {}

    F f;
};

int main() {}