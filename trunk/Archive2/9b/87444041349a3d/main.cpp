#include <list>
#include <iostream>

template<typename S, typename T>
S& operator<<(S& s, const std::list<T>& l)
{
    s << "{ ";
	for (auto i:l) s << i << " ";
	return s << "}";
}

template<typename L, typename I>
void inner(L& l, I b, I e)
{
	L t;
	t.splice(t.end(), l, b, e);  // t = {3 2 5}; l = {4 0 1}
	t.reverse();                 // t = {5 2 3}
	l.splice(e, t);              // l = {4 5 2 3 0 1}; t = {}
}

template<typename L, typename I>
void outer(L& l, I b, I e)
{
	l.splice(l.begin(), l, e, l.end());  // l = {0 1 4 3 2 5}
	inner(l, l.begin(), b);              // l = {4 1 0 3 2 5}
}

int main ()
{
	std::list<int> t, l{4, 3, 2, 5, 0, 1};
	std::cout << l << std::endl;

	auto b = l.begin(), e = l.begin();
	std::advance(b, 1);
	std::advance(e, 4);
	bool in = true;

	in ? inner(l, b, e) : outer(l, b, e);
	std::cout << l << std::endl;
}
