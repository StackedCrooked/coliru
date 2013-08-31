struct foo { int i; };
struct bar: foo { using ::foo::i; };

int main()
{}