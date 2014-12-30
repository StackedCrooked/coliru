struct A
{A() = default; A(A&&) = default; A(A const&) = delete;};

int main()
{A a; throw a;}