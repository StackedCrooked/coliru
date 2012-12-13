struct Base{};
struct Derived : Base{};

int main() {
    Base *b = new Derived();
    Derived *d = b;
}