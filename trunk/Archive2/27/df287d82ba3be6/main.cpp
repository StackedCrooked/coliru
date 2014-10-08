#include <iostream>
#include <functional>
#include <memory>

// Predefine template delegate factory
template < typename R, typename... Args >
class brGenericDelegate ;

// C++11 template alias to announce functor definition
template < typename R, typename... Args >
using brGenericDelegateType = std::function< std::shared_ptr<R>(Args...) > ;

class brDelegate
{
protected:
    brDelegate(){}

public:
    virtual ~brDelegate() = default ;
    virtual bool operator== ( const brDelegate& that ) const { return typeid(*this) == typeid(that) ; }
    virtual bool operator!= ( const brDelegate& that ) const { return !( *this == that ) ; }

    template < typename R, typename... Args >
    static std::shared_ptr<brDelegate> create( typename brGenericDelegate<R,Args...>::functor func )
	{
		return std::make_shared<brGenericDelegate<R,Args...>>(func) ;
	}


    template < typename R, typename... Args >
	std::shared_ptr<R> run( Args... args ) const
    {
        using derived_type = brGenericDelegate<R,Args...> ;
        return dynamic_cast< const derived_type& >(*this)(args...) ;
    }
};

bool operator== ( const std::shared_ptr<brDelegate>& a, std::shared_ptr<brDelegate>& b )
{
    if( a && b ) return *a == *b ;
    else return !a && !b ;
}

bool operator!= ( const std::shared_ptr<brDelegate>& a, std::shared_ptr<brDelegate>& b ) { return !( a == b ) ; }

template < typename R, typename... Args >
class brGenericDelegate : public brDelegate
{
public:
    using functor = brGenericDelegateType< R, Args... >;
    brGenericDelegate( functor f ) : fn(f) {}

    std::shared_ptr<R> operator() ( Args... args ) const { return fn(args...) ; }

private:
    const functor fn ;
};

struct IUser { virtual ~IUser() = default ; };
struct User : IUser { User( const char* = nullptr, int = 0 ) {} };

int main()
{
    auto d1 = brDelegate::create<User>([] () -> std::shared_ptr<User> { return std::make_shared<User>(); });
    auto d2 =  brDelegate::create<IUser, int>([] (int age) -> std::shared_ptr<IUser> { return std::make_shared<User>("Klaus", age); });
    auto d3 = brDelegate::create<IUser, int>([] (int age) -> std::shared_ptr<IUser> { return std::make_shared<User>("Klaus", age); });

    std::cout << std::boolalpha << ( d1 == d2 ) << '\n' // false
              << ( d2 == d3 ) << '\n' ; // true

}
