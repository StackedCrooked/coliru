struct Base{};

struct Derived : Base {
    Derived() : ::Base{}, Base{} {}
    int Base;  
};

int main() {}