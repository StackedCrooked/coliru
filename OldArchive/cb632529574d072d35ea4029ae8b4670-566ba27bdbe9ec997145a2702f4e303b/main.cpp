

template<int...> struct X{};

template<int...> struct concatenate{};

template<int... l, int... r> struct concatenate{
    typedef X<l...,r...> concatenated;
};


int main()
{

	typedef concatenate<X<1,2,3>,X<4,5,6>>::concatenated Z;

}