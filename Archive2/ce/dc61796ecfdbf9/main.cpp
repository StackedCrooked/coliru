
#include <vector>
#include <utility>

using namespace std;

struct A {
    A(int i=0) : i(i)  {}
    int i;
};

struct B { vector<A> v; };

template <typename C,typename I> C&& f( C&& c, I && i ) {
	return move(c);
}

int main() {
	B b{ f( vector<A>{}, move(A{}) ) };
}






