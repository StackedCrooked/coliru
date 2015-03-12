#include <iostream>
#include <utility>

using namespace std;

struct Member
{
    Member () {}
	Member (Member const&) { cout << "member: copy ctor\n"; }
	Member (Member&&) = delete;
};

struct Base
{
	Base () {}
	Base (Base const&) { cout << "base: copy ctor\n"; }
	Base (Base&&) = delete;
};

struct Class : Base
{
	Member m;
};

int main ()
{
	Class a;
	cout << "move class: a -> b\n";
	Class b { move (a) };
}
