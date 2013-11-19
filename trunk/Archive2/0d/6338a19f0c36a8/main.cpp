#include <iostream>
#include <memory>
#include <utility>
#include <typeindex>
#include <type_traits>
#include <map>
#include <vector>

// c++14 add "add_pointer_t" helper
#if !defined(_MSC_VER) || ( _MSC_VER < 1800 )
namespace std {
    template <typename T>
	using add_pointer_t = typename std::add_pointer<T>::type;
}
#endif

template < typename Key, typename Object >
class Factory{
private:
	using FakeCreatorFunc = std::add_pointer_t< Object* () >;
	template < typename... Args >
	using RealCreatorFunc = std::add_pointer_t< Object* ( Args... ) >;

	using RealKey    = std::pair< Key, std::type_index >;
	using CreatorMap = std::map< RealKey, FakeCreatorFunc >;

	template < typename T, typename... Args >
	static Object * CreateFunc( Args... args ) {
		return new T { std::forward<Args>( args )... };
	}

	CreatorMap creators_;

public:
	using ResultType = std::unique_ptr<Object>;

	template < typename T, typename... Args >
	typename std::enable_if< std::is_base_of<Object, T>::value &&
		std::is_constructible<T, Args...>::value, bool >::type RegisterItem( Key key ) {
			RealKey realKey { key, std::type_index( typeid( RealCreatorFunc<Args...> ) ) };
			auto it = creators_.find( realKey );
			if ( it != creators_.end( ) )
				return false;
			creators_[ realKey ] = reinterpret_cast<FakeCreatorFunc>( CreateFunc<T, Args...> );
			return true;
		}

	template < typename... Args >
	ResultType Create( Key key, Args... args ) {
		RealKey realKey { key, std::type_index( typeid( RealCreatorFunc<Args...> ) ) };
		auto it = creators_.find( realKey );
		if ( it == creators_.end( ) )
			return {};
		auto creator = reinterpret_cast<RealCreatorFunc<Args...>>( it->second );
		return std::unique_ptr<Object> { creator( std::forward<Args>( args )... ) };
	}
};

struct Shape {
	virtual ~Shape( ) {}
	virtual void Display( std::ostream& ) const = 0;
protected:
	Shape( ) {}
};

struct Circle : public Shape {
	Circle( ) = default;
	Circle( float rad ) : radius_ { rad } {}
	void Display( std::ostream& os ) const override { os << "Circle ( " << radius_ << " )"; }
private:
	float radius_ = 1.f;
};

struct Rect : public Shape {
	Rect( ) = default;
	Rect( float w, float h ) : w_ { w }, h_ { h } {}
	void Display( std::ostream& os) const override { os << "Rect ( " << w_ << " x " << h_ << " )"; }
private:
	float w_ = 5.f;
	float h_ = 5.f;
};
enum class Shapes {
	CIRCLE = 0,
	RECT,
};



std::ostream& operator<<( std::ostream& os, std::unique_ptr<Shape> const & ptr ) {
	if ( ptr ) {
		ptr->Display( os );
	} else {
		os << "Empty Shape";
	}
	return os;
}

int main( ) {
	Factory< Shapes, Shape > theFactory;

	theFactory.RegisterItem<Circle, float>( Shapes::CIRCLE );
	theFactory.RegisterItem<Rect, float, float>( Shapes::RECT );
	theFactory.RegisterItem<Rect>( Shapes::RECT );

	std::vector< std::unique_ptr<Shape> > shapes;
	shapes.reserve( 16 );
	
	shapes.push_back( std::move( theFactory.Create( Shapes::CIRCLE, 2.f ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::CIRCLE, 1 ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT, 1 ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT, 3.f, 4.f ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT ) ) );
	
	std::cout.precision( 2 ); std::cout << std::fixed;

	for( auto const & shape : shapes ) 
		std::cout << shape << std::endl;

	return 0;
}