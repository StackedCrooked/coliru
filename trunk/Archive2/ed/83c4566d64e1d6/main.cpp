#include <iterator>
#include <type_traits>
#include <typeinfo>

#include <iostream>

struct test {
    int a;
	void meow( double x ) {
		auto purr = [ self = *this ]( auto&& p ) {
			self.a += static_cast<int>(p);
		};
		purr( x );
	}

};

int main( ) {
	test t{};
	t.meow( 2.0 );
}