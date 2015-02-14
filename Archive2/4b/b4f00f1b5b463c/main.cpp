
template < typename T > struct foo
{
    T bar( T a ) { return a + 2 ; }

    template < typename U > U baz( U a ) { return a % 2 ; }
};

// explicit instantiation of class foo<double>
template struct foo<double> ; // double foo<double>::bar(double) is instantiated
                              // U foo<double>::baz<U>(U) is not instantiated for any U

// explicit instantiation of long foo<int>::baz<long>(long)
template long foo<int>::baz(long) ; // fine

int main()
{
}

// explicit instantiation of double foo<int>::baz<double>(double)
template double foo<int>::baz(double) ; // **** error: invalid type double in a % 2
