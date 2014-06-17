template <typename T>
class Foo {
public:
  enum Mode { Mode1, Mode2, Mode3 };
};


int main() {
    Foo<float> foo;
    auto m = decltype(foo)::Mode1;
}