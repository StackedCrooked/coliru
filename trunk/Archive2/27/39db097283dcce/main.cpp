class Cvector
{
    public:
        int x, y;
        Cvector () {};
        Cvector ( int a, int b ) : x( a ), y( b ) {}
};

int main()
{
    Cvector fooF2 ( 1, 1 ) ; // this can't be a declaration; no mvp
    fooF2 = { 1, 2 } ; // fine
    
    Cvector fooF3 { int(), int() } ; // this can't be a declaration; no mvp
    fooF3 = { 1, 2 } ; // fine
    
    Cvector fooF4 ( int {}, int {} ) ; // this can't be a declaration; no mvp
    fooF4 = { 1, 2 } ; // fine
    
    Cvector fooF5 ( int(), int{} ) ; // this can't be a declaration; no mvp
    fooF5 = { 1, 2 } ; // fine
    
    Cvector fooF6 ( int(), int() ) ; // this can be a declaration; mvp
    // *** warning: parentheses were disambiguated as a function declaration [-Wvexing-parse]
    // ** note: add a pair of parentheses to declare a variable
    fooF6 = { 1, 2 } ; // **** error: assignment to function

    Cvector fooF7 ( ( int() ), int{} ) ; // this can't be a declaration; no mvp
    fooF7 = { 1, 2 } ; // fine
}
