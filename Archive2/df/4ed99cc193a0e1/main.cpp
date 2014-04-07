#include <list>
#include <algorithm>
#include <iostream>

template<typename S, typename T>
S& operator<<(S& s, const std::list<T>& l)
{
    s << "{ ";
	for (auto i:l) s << i << " ";
	return s << "}";
}

template<typename I>
void inner(I b, I e)
{
    std::reverse(b, e);  // l = {4 5 2 3 0 1}
}

template<typename L, typename I>
void outer(L& l, I b, I e)
{
	l.splice(l.begin(), l, e, l.end());  // l = {0 1 4 3 2 5}
	std::reverse(l.begin(), b);          // l = {4 1 0 3 2 5}
}

int main ()
{
	std::list<int> t, l{4, 3, 2, 5, 0, 1};
	std::cout << l << std::endl;

	auto b = l.begin(), e = l.begin();
	std::advance(b, 1);
	std::advance(e, 4);
	bool in = true;

	in ? inner(b, e) : outer(l, b, e);
	std::cout << l << std::endl;
}
