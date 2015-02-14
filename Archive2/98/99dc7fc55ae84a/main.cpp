
template < typename T > struct foo
{
    T bar( T a ) { return a + 2 ; }

    template < int N, typename U > U baz( U a ) { return a % N ; }
};

// explicit instantiation of class foo<double>
template struct foo<double> ; // double foo<double>::bar(double) is instantiated
                              // U foo<double>::baz<U>(U) is not instantiated for any U

// explicit instantiation of long foo<int>::baz<8,long>(long)
template long foo<int>::baz<8>(long) ; // fine: U == long is deduced

int main()
{
}

// explicit instantiation of double foo<int>::baz<22,double>(double)
// template double foo<int>::baz<22>(double) ; // **** error: invalid type double in a % 22
