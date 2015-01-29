#include <type_traits>

template <class T> struct A{

    template <class is_const> struct B { 
		friend struct B < std::conditional_t < is_const{}, std::false_type, 
														std::true_type >> ; 

		private:
 		int b;

		template<class Constness>
		int foo(B<Constness> other) { return other.b; }
	}; 

	auto const_b() { return B<std::true_type>{}; }
	auto non_const_b() { return B<std::false_type>{}; }

};

int main() {
	A<int> a;
	auto c = a.const_b();
	auto nc = a.non_const_b();
	
	auto i = c.foo(c);
	auto i2 = c.foo(nc);
	auto i3 = nc.foo(c);	
	auto i4 = nc.foo(nc);
	return i + i2 + i3 + i4;
}