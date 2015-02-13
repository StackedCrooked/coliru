namespace n
{
    template <typename T>
	void foo(T const & t)
	{
		t.doesnt_have_this_method();
	}
}

// Will compile correctly if this is moved down right before main.
template <typename T>
void bar(T const & t)
{
    using namespace n;
    foo(t);
}

class A
{};

namespace n
{
	void foo(A const &);
}

void n::foo(A const &)
{
}


int main()
{
	A a;

	bar(a);

	return 0;
}
