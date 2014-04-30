using vi_ft = void(int);

class B {
public:
    vi_ft baz, qux;
};
void B::baz(int) {}
void B::qux(int) {}

void fred(bool x) {
    B b;
    vi_ft B::*f{ x ? &B::baz : &B::qux };
    (b.*f)(0);
}

int main() {
    fred(true);
    fred(false);
}
