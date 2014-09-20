#include <iostream>
#include <memory>
#include <type_traits>
#include <typeindex>
#include <map>

 struct factory
{
    virtual ~factory() = default ;

    template < typename T, typename... ARGS > static std::shared_ptr<T> create( ARGS... args )
    {
        auto p = get<T>() ;
        return p ? p->create( args... ) : nullptr ;
    }

    factory( const std::type_info& ti ) : key(ti) { map.emplace(key,this) ; }

    private:
        std::type_index key ;
        static std::map< std::type_index, factory* > map ;

        template < typename T > static typename T::factory_type* get()
        {
            const auto iter = map.find( typeid(T) ) ;
            return iter == map.end() ? nullptr : dynamic_cast<typename T::factory_type*>(iter->second) ;
        }
};

std::map< std::type_index, factory* > factory::map ;

template < typename T > struct default_factory : factory
{
    using type = T ;

    default_factory() : factory( typeid(T) ) {}

    template < typename... ARGS > std::shared_ptr<T> create( ARGS... args )
    { return std::make_shared<T>( args... ) ; }
};

template < typename T > struct with_default_factory
{
    using factory_type = default_factory<T> ;
    static factory_type Tfactory ;
    const bool force_instantiation = std::addressof(Tfactory) ;
};

template < typename T > typename with_default_factory<T>::factory_type with_default_factory<T>::Tfactory ;

struct A : with_default_factory<A>
{
    A() { std::cout << "A::default constructor\n" ; }
    A(int) { std::cout << "A::A(int)\n" ; }
    A(int,double) { std::cout << "A::A( int, double )\n" ; }
    ~A() { std::cout << "A::destructor\n" ; }
};

struct B_factory ;
struct B // type with custom factory
{
    using factory_type = B_factory ; // announce factory type
    ~B() { std::cout << "B::destructor\n" ; }
};

struct B_factory : factory // custom factory, must derive from factory
{
    using type = B ; // announce type being created

    B_factory() : factory( typeid(B) ) {} // instantiate base class with type_index of the type

    std::shared_ptr<B> create( const char* msg )
    {
        ++create_cnt ; 
        std::cout << "B_factory::create( '" << msg << "' )\n" ;
        return std::make_shared<B>() ;
    }
    
    std::shared_ptr<B> create( const char* msg1, const char* msg2  )
    {
        ++create_cnt ; 
        std::cout << "B_factory::create( '" << msg1 << "', '" << msg2 << "' )\n" ;
        return std::make_shared<B>() ;
    }
    
    int create_cnt = 0 ;
};

B_factory bfactory ; // instantiate a factory instance (typically, a singleton)

int main()
{
    auto p1 = factory::create<A>() ;
    auto p2 = factory::create<A>(56) ;
    auto p3 = factory::create<A>( 56, 678.9 ) ;
    auto p4 = factory::create<B>( "hello" ) ;
    auto p5 = factory::create<B>( "hello", "world" ) ;
    std::cout << bfactory.create_cnt << '\n' ;
}
