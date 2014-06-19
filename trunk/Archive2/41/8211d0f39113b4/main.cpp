using F = int( int, int );

F f; // declare int f( int, int );

int main()
{
    f( 1, 2 );
}

// the definition can't be done using F
int f( int a, int b )
{
    return a + b;
}
