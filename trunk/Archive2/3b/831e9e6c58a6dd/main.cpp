struct A
{
private:
    A() = default;
public:
    int i;
    int j = 42;
    A(int foo) : i(foo) {}
};

int main() {
    A a{};
}
