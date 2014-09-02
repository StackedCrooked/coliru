struct stuff {
    enum type {
        a, b, c
    };
};

using flags = stuff::type;

int main() {
    flags x = flags::a | flags::b;
}