struct A
{
private:
    A() = default;
public:
    int i;
    int j = 42;
    static void im_a_member() {
        A a{};
    }
};

int main() {
    A a{};
}
