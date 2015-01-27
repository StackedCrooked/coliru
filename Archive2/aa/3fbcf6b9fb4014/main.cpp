template<class T> struct A {
    struct B {};
    struct D {
		void g();
	};
};
template<> struct A<int> {
    struct B {};
	struct D {
		void g();
	};
};

class C {
    template<class T> friend struct A<T>::B;
    template<class T> friend void A<T>::D::g();
};	
