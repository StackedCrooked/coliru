template <unsigned int N>
struct Wrapper {
    enum { ctc_wrapped_val = N };
};

template <unsigned int N>
struct Foo {

	enum { first = 2, second = 4 };

	template <unsigned int M>
	constexpr unsigned int at(Wrapper<M> const& par) {
		return (par.ctc_wrapped_val == 0) ? first : second;
	}
};

template <unsigned int N> struct begin_error;

int main() {
	Foo<0> f;
	//(Foo<0>{}).at(  ( Wrapper<0>{} ).ctc_wrapped_val  );
	
	Wrapper<0> w;
	//begin_error<w.ctc_wrapped_val> end_error;
	begin_error< f.at(w) > end_error;
}

//begin_error<Foo<3>::first> end_error;
//begin_error<Foo<3>::second> end_error;