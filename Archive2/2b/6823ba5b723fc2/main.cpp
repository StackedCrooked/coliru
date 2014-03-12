template<typename T>
struct name {};

struct A
{
    template<bool B>
	void name() { }
};

template <bool B, typename T>
void f(T&& x) { x.template name<true>(); }

int main
{
}