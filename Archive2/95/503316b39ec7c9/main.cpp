template< bool... Bs >
void func();

template< bool... Bs, typename... Ts >
void func( bool b, Ts... ts )
{
    if( b ) {
        func< Bs..., true >( ts... );
    }
    else {
        func< Bs..., false >( ts... );
    }
}

int main()
{
    func( true, false, true, true );
}
