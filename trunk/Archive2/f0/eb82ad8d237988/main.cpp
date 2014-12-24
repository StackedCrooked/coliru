#include <iostream>
#include <string>
#include <utility>

struct A {
    struct Tag{};
	std::string name;
	int value;
	A (const std::string& n, int v) : name(n), value(v) {}
	A (const std::string& n, int v, Tag) : name(n), value(v) {std::cout << "Constructor with Tag called.\n";}
};

struct B : A {using A::A;};
struct C : B {using B::B;};

struct D : C {
	char special;
	template < typename ... ARGS >
	D( const std::string& n, int v, char s, ARGS&&... args ) : C( n, v, std::forward<ARGS>(args)... ), special(s) {}
};

struct E : B {
	double special;
	template < typename ... ARGS >
	E( const std::string& n, int v, double d, ARGS&&... args ) : B( n, v, std::forward<ARGS>(args)... ), special(d) {}
};

int main() {
	A a("a", 1, A::Tag{});
	B b("a", 2, A::Tag{});
	C c("c", 3, A::Tag{});
	D d("d", 4, 'd', A::Tag{});
	E e("e", 5, 3.14, A::Tag{});
}
