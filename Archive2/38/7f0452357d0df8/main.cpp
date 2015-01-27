template<class T> struct A {
    struct D {
		void g();
	};
};
template<> struct A<int> {
	struct D {
		void g();
	};
};

class C {
    template<class T> friend void A<T>::D::g();
};	
