#include <iostream>

struct B
{
    struct logger ;
    explicit B( logger& lg ) : the_logger(lg) {}

    void foo() const { the_logger.print( "hello from B::foo" ) ; }

    struct logger
    {
      virtual ~logger() {}
      private: virtual void print( const char* ) const = 0 ;
      friend B ;
    };

    private: logger& the_logger ;
};

int main()
{
    struct logger_impl : B::logger
    {
        private: virtual void print( const char* cstr ) const override
        { std::cout << "logger_impl::print: '" << cstr << "'\n" ; }
    };

    logger_impl logger ;
    B b( logger ) ;
    b.foo() ;
}
