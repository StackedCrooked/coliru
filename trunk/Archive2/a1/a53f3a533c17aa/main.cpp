struct test {
public:
    
    template <unsigned int n>
    test ( const char (&x)[n] ) {
        
    }
};

template <typename T>
struct testa {
public:
    
    template <unsigned int n>
    testa ( T (&x)[n] ) {
        
    }
};

struct aggregate {
public:
    testa<const char> arf;
    
};

int main () {
    test t1 = test( "arf" );
    test t2( "arf" );
    test t3 = test{ "arf" };
    test t4 = { "arf" };
    test t5{ "arf" };
    
    testa<const char> ta1 = testa<const char>( "arf" );
    testa<const char> ta2( "arf" );
    testa<const char> ta3 = testa<const char>{ "arf" };
    testa<const char> ta4 = { "arf" };
    testa<const char> ta5{ "arf" };
    
    aggregate aggregatetest[] = {
       { "arf" }
    };
}
