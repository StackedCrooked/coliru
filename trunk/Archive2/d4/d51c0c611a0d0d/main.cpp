struct A
{
private:
    A() = default;
public:
    int i;
    int j = 42;
    static void im_a_member() {
        // Ok, bullet two zeroes the object
        // and doesn't call the (trivial) default constructor.
        A a{};
    }
};

int main() {
    // Ill-formed, bullet two zeroes the object
    // but the semantic constraint check fails since the default constructor
    // is inaccessible, even though it would not actually be called.
    A a{};
}
