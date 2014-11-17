struct A
{
    A(int, int) {}

	A(A const&) = delete;
    A(A &&) = delete;
};

void foo(A) {}

int main()
{
	foo({1, 2});
}
