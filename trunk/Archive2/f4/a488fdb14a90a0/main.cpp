#include <algorithm>

struct S
{
    static const int i = -1;
	static constexpr double d = 0.001;
};

template <class T>
T ref(const T& i)
{
	return i;
}

template <class T>
T value(const T i)
{
	return i;
}

int main()
{
	value(S::i);
	value(S::d);

    std::max(4, S::i); // error

	ref(S::i); // error
	ref(S::d); // error
}
