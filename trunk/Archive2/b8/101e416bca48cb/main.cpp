#include <iostream>

using namespace std;

struct WeirdClass { int eird; };

struct MyCT { virtual int fuz() const = 0; };

struct foo : MyCT
{
    virtual int fuz() const override { return 4; };
};

struct bar : MyCT
{
	int b;
	bar(int b) : b(b) { }
	virtual int fuz() const override { return 2 * b; };
};

struct baz : MyCT
{
	WeirdClass w;
	baz(const WeirdClass& w) : w(w) { }
	virtual int fuz() const override { return w.eird; };
};

struct bat : MyCT
{
	std::string s;
	const MyCT& m;
	bat(const std::string& s, const MyCT& m) : s(s), m(m) { }
	virtual int fuz() const override { return (int)s.length() - m.fuz(); };
};

int main()
{
	foo f;
	bar r{-20}, c{626};
	baz z{{8}};
	bat a{"Like I said",f};
	bat t{"a",c};

	cout << f.fuz() << " " <<  r.fuz() << " "
	     << c.fuz() << " " <<  z.fuz() << " "
	     << a.fuz() << " " <<  t.fuz() << endl;
}
