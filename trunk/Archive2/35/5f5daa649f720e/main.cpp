#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <memory>
#include <typeindex>

template < typename Key, typename Object >
class Factory{
    private:
	using FakeCreatorFunc = Object* (*)( );

	struct RealKey {
		RealKey() = delete;
		Key first;
		std::type_index second;
		friend bool operator<( RealKey const & a, RealKey const & b ) {
			return ( a.first < b.first ) || ( a.first == b.first && a.second < b.second );
		}
	};
	using CreatorMap = std::map<RealKey, FakeCreatorFunc>;
	CreatorMap creators_;

public:
	template < typename funcT >
	bool registerItem( Key key, funcT creator )
	{
		RealKey realKey { key, std::type_index( typeid( creator ) ) };
		if ( creators_.find( realKey ) != creators_.end( ) )
			return false;
		creators_[ realKey ] = reinterpret_cast<FakeCreatorFunc>( creator );
		return true;
	}

	template < typename... args >
	std::unique_ptr<Object> create( Key key, args... arguments )
	{
		using RealCreatorFunc = Object*  (*)( args... );
		RealKey realKey { key, std::type_index( typeid( RealCreatorFunc ) ) };

		auto it = creators_.find( realKey );
		if ( it == creators_.end() )
			return {};
		auto creator = reinterpret_cast<RealCreatorFunc>( it->second );
		return std::unique_ptr<Object> { creator( std::forward<args>( arguments )... ) };
	}
};

struct Shape {
	virtual ~Shape( ) {}
protected:
	Shape( ) {}
};

struct Circle : public Shape {
	Circle( ) = default;
	Circle( float rad ) : radius_ { rad } {}
	float radius_;
};

struct Rect : public Shape {
	Rect( ) = default;
	Rect( float w, float h ) : w_ { w }, h_ { h } {}
	float w_;
	float h_;
};


Factory<std::string, Shape > theFactory;

template < typename Base, typename Real, typename... args >
typename std::enable_if< std::is_base_of<Base,Real>::value && 
                         std::is_constructible<Real, args...>::value, Base* >::type
creatorFunc( args... arguments ) {
	return new Real (std::forward<args>( arguments )... );
}

int main( )
{
	theFactory.registerItem( "Circle", &creatorFunc<Shape, Circle, float> );
	theFactory.registerItem( "Rect", &creatorFunc<Shape, Rect, float, float> );
	
	auto shape01 = theFactory.create( "Circle", 2.f );
	auto shape02 = theFactory.create( "Circle", 1 );
	auto shape03 = theFactory.create( "Rect", 1 );
	auto shape04 = theFactory.create( "Rect", 1.f, 2.f );

    std::cout << std::boolalpha;
	std::cout << bool( shape01 ) << std::endl;
	std::cout << bool( shape02 ) << std::endl;
	std::cout << bool( shape03 ) << std::endl;
	std::cout << bool( shape04 ) << std::endl;

	return 0;
}