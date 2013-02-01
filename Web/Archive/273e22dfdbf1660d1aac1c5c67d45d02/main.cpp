class Foo {
public:
  Foo& operator=(const Foo&) = default;
private:
  const int i = 0;
};

int main() {
    Foo f;
    f = f;
}