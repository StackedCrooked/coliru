#include <iostream>
#include <string>
#include <cmath>

int foo (int num) {return num;}
int foo (double num) {return std::round (num);}
int foo (std::string str) {return str.length();}

template <class T>
struct predicate_and_action {
    void operator() (const T& t ) const {
        if (foo(t) == 5) std::cout << "Hooray!" << std::endl;
    }
};

template < template<typename> class PREDICATE_AND_ACTION, class T >
void check ( const T& t) {
	PREDICATE_AND_ACTION<T>()(t);
}

template < template<typename> class PREDICATE_AND_ACTION, class FIRST, class...REST >
void check( const FIRST& first, const REST&...rest) {
	PREDICATE_AND_ACTION<FIRST>()(first);
	check<PREDICATE_AND_ACTION>( rest... );
}

int main() {
	check<predicate_and_action>( 5, 4.9, "smile" );
	//std::cin.get();
} 
