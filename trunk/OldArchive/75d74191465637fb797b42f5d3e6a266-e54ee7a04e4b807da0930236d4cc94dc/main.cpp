namespace ns {
    template<typename T> inline T f() { return T(); }
    template<> inline double f<double>() { return 0.001; } // test specialization
};
template<typename T >
class A1 {
    public: A1( const T& arg = ns::f<T>() );
};
template<typename T>
class D1 {
    public: D1(T t = 0) : t_(t) {};
    private: T t_;
};
class my {
    A1< D1<int> > a;

    public: my() ;
};

//namespace ns { template<> D1<int>  f<D1<int> >() { return D1<int>(); } }

my::my() { };

void ff() {
    my m;
    A1<double> ad;
}

int main()
{
    return 0;
}
