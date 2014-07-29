template<typename Compare>
struct MyMap
{
    Compare c;

	MyMap(Compare const &c = Compare()): c(c) {}

	bool do_compare(int a, int b) const { Compare d = c; return d(a, b); }
};

struct Foo
{
	Foo(int) {}

	bool operator()(int a, int b)
	{
		return a < b;
	}
};

int main(int argc, char **argv)
{
	MyMap<Foo> const m(Foo(1));
	m.do_compare(1, 2);
}
