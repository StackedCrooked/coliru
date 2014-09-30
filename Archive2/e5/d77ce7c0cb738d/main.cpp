template<class T>
void foo(T&) {}

struct X {};

int main()
{
    typedef X const CX;
    foo( CX() ); // fine
    foo( X() ); // error
    
    typedef int const CI;
    foo( CI() ); // error
}