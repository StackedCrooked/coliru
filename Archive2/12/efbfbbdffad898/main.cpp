    #include <iostream>
    #include <chrono>
    #include <string>
    #include <functional>
    #include <vector>
    #include <unordered_map>
    
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;
    using std::chrono::high_resolution_clock;
    using std::string;
    
    std::vector< int > output;
    
    struct Base {
        const int i{-1};
        const float f{3.1415};
        const string str{"Howdy"};
        Base( int i ) : i{i} {}
    };
        
    struct Foo {
        Foo(int num) : num_(num) {}
        int print_add( const Base & b ) const {
            output.push_back( num_+b.i );
            return 0;
        }
        int num_;
    };
 
    int print_num( const Base & b )
    {
        output.push_back( b.i );
        return 0;
    }
 
    struct PrintNum {
        int operator()( const Base & b ) const
        {
            output.push_back( b.i );
            return 0;
        }
    };

    int main( int argc, char *argv[] )
    {
        using Dispatcher = std::unordered_map< uint16_t, std::function< int( const Base & ) > >;
        
        Dispatcher d;

        using std::placeholders::_1;
        const Foo foo(314159);
        const Base b(31337);
 
        //-- Add to the dispatcher a bunch of different functions
        
        d[0] = &Foo::print_add;  // store a call to a member function
        d[1] = print_num;  // store a free function
        d[2] = [](const Base& x) { print_num(x); }; // store a lambda
        d[3] = std::bind(print_num, 31337); // store the result of a call to std::bind
        d[4] = std::bind( &Foo::print_add, foo, _1 ); // store a call to a member function and object
        d[5] = std::bind( &Foo::print_add, &foo, _1 );   // store a call to a member function and object ptr       
        d[6] = PrintNum(); // store a call to a function object
        
        //-- Call all the functions using the dispatcher and the numeric key

        high_resolution_clock::time_point start = high_resolution_clock::now();
        
        static constexpr size_t ITERATIONS = 1000000;
        
        for( size_t i = 0; i < ITERATIONS; ++i ) {
            output.clear();
            d[1]( Base{-9} );
            d[2]( Base{42} );
            d[3]( b );
            d[4]( Base{2} );
            d[5]( Base{3} );
            d[6]( Base{18} );
        }
        
        high_resolution_clock::time_point end = high_resolution_clock::now();

        for( int x : output ) std::cout << x << std::endl;
        
        std::cout << duration_cast<nanoseconds>(end - start).count() / (output.size() * ITERATIONS) << " average nsec / dispatch\n";

        return 0;
    }
