template <typename T>
struct lambda;

template <template <typename A0> class Tem, typename A0>
struct lambda<Tem<A0>> {
	struct type {
		template <typename a0>
		struct apply : Tem<typename A0::template apply<a0>::type> {};	
	};
};

template <typename T>
struct Foo {};


int main() {
    typedef lambda<Foo<int>>::type Foo;
    
    //typedef lambda<int>::type Int; //error: 'type' in 'struct lambda<int>' does not name a type
    
    return 0;
}