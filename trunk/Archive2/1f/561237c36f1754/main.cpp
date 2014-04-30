#include <utility>

struct A
{
    template<typename T> explicit operator T&&       () &&;
	template<typename T> explicit operator T&        () &;
	template<typename T> explicit operator const T&  () const&;
};

struct B {};

int main ()
{
	A a;

	A&&      ar = std::move(a);
	A&       al = a;
	const A& ac = a;

	B&&      bm(std::move(a));  // 1. OK
	B&&      bt(A{});           // 2. OK
	B&&      br(ar);            // 3. error: no viable conversion from A to B
	B&       bl(al);            // 4. OK
	const B& bz(al);            // 5. OK
	const B& bc(ac);            // 6. OK

	B        cm(std::move(a));  // 7. error: call to constructor of B ambiguous
	B        ct(A{});           // 8. error: call to constructor of B ambiguous
	B        cr(ar);            // 9. OK
}
