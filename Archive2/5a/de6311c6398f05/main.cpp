class Base {};

class Derived : public Base{};

void f(Base b) { }

int main() {
    Derived d;
	f(d);
}
