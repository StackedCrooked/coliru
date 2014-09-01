struct base {
    int x;
    int y;
};

struct derived : base {
    derived(): base{10, 10} {}
};


int f(const base& b) {
    return b.x + b.y;
}

int main() {
    return f(derived{});
}