template<typename Compare>
struct MyMap
{
    Compare c;

	MyMap(Compare const &c = Compare()): c(c) {}

	bool do_something() const { Compare d = c; return d(1, 2); }
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
	m.do_something();	
}
