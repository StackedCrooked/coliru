    #include <iostream>
    #include <chrono>
    #include <functional>
    #include <vector>
    #include <unordered_map>
    
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;
    using std::chrono::high_resolution_clock;

    std::vector< int > output;
    
    struct Foo {
        Foo(int num) : num_(num) {}
        void print_add(int i) const { output.push_back( num_+i ); }
        int num_;
    };
 
    void print_num(int i)
    {
        output.push_back( i );
    }
 
    struct PrintNum {
        void operator()(int i) const
        {
            output.push_back( i );
        }
    };

    int main( int argc, char *argv[] )
    {
        using Dispatcher = std::unordered_map< uint16_t, std::function< void( int ) > >;
        
        Dispatcher d;

        using std::placeholders::_1;

        // store a call to a member function
        std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
        const Foo foo(314159);
 
        //-- Add to the dispatcher a bunch of different functions
        
        d[1] = print_num;  // store a free function
        d[2] = [](int x) { print_num(x); }; // store a lambda
        d[3] = std::bind(print_num, 31337); // store the result of a call to std::bind
        d[4] = std::bind( &Foo::print_add, foo, _1 ); // store a call to a member function and object
        d[5] = std::bind( &Foo::print_add, &foo, _1 );   // store a call to a member function and object ptr       
        d[6] = PrintNum(); // store a call to a function object
        
        //-- Call all the functions using the dispatcher and the numeric key

        high_resolution_clock::time_point start = high_resolution_clock::now();
        
        static constexpr size_t ITERATIONS = 1000000;
        
        for( size_t i = 0; i < ITERATIONS; ++i ) {
            output.clear();
            d[1]( -9 );
            d[2]( 42 );
            d[3](  0 );
            d[4](  2 );
            d[5](  3 );
            d[6]( 18 );
        }
        
        high_resolution_clock::time_point end = high_resolution_clock::now();

        for( int x : output ) std::cout << x << std::endl;
        
        std::cout << duration_cast<nanoseconds>(end - start).count() / (output.size() * ITERATIONS) << " average nsec / dispatch\n";

        return 0;
    }
