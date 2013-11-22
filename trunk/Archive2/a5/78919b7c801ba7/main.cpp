#include <iostream>
#include <memory>
#include <utility>
#include <typeindex>
#include <type_traits>
#include <map>
#include <vector>
#include <exception>
#include <iomanip>

// c++14 add type trait helpers http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3655.pdf
#if !defined(_MSC_VER) || ( _MSC_VER < 1800 )
namespace std {
    template <typename T>
	using add_pointer_t = typename std::add_pointer<T>::type;
}
#endif

template < typename Key, typename Object >
class Factory{
	static_assert( std::has_virtual_destructor<Object>::value, "base class must declare a virtual destructor" );

	template < typename... Args >
	using RealCreatorFunc = std::add_pointer_t< Object* ( Args... ) >;
	using FakeCreatorFunc = std::add_pointer_t< Object* () >;
		
	template < typename T, typename... Args >
	static Object * CreateFunc( Args... args ) {
		return new T { std::forward<Args>( args )... };
	}
	
	using RealKey    = std::pair< Key, std::type_index >;
	using CreatorMap = std::map< RealKey, FakeCreatorFunc >;
	CreatorMap creators_;

public:
	using ResultType = std::unique_ptr<Object>;
	
	template < typename T, typename... Args >
	bool RegisterItem( Key key ) {
		static_assert( std::is_base_of<Object, T>::value, "RegisterItem, T must be a subclass of Object" );
		static_assert( std::is_constructible<T, Args...>::value, "RegisterItem, T must be constructible with Args..." );
		return creators_.emplace( RealKey { key, std::type_index( typeid( RealCreatorFunc<Args...> ) ) }
		, reinterpret_cast<FakeCreatorFunc>( CreateFunc<T, Args...> ) ).second;
	}

	// the static_assert version provide friendlier compiler error than the enable_if solution.
	// Kept for reference.
	//template < typename T, typename... Args >
	//auto RegisterItem( Key key ) -> typename std::enable_if< std::is_base_of<Object, T>::value &&
	//std::is_constructible<T, Args...>::value, bool >::type {
	//return creators_.emplace( RealKey { key, std::type_index( typeid( RealCreatorFunc<Args...> ) ) }
	//, reinterpret_cast<FakeCreatorFunc>( CreateFunc<T, Args...> ) ).second;
	//}

	template < typename... Args >
	ResultType Create( Key key, Args... args ) try {
		auto fakeCreator = creators_.at( { key, std::type_index( typeid( RealCreatorFunc<Args...> ) ) } );
		auto creator = reinterpret_cast<RealCreatorFunc<Args...>>( fakeCreator );
		return ResultType { creator( std::forward<Args>( args )... ) };
	} catch ( std::out_of_range const & ) {
		std::cerr << "Request an invalid construction." << std::endl;
		return {};
	}
};

struct Shape {
	Shape( Shape const & ) = delete;
	Shape( Shape && ) = delete;
	Shape& operator=( Shape const & ) = delete;
	Shape& operator=( Shape && ) = delete;

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

int main() {
	Factory< Shapes, Shape > theFactory;

    theFactory.RegisterItem<Circle>( Shapes::CIRCLE );
	theFactory.RegisterItem<Circle, float>( Shapes::CIRCLE );
	theFactory.RegisterItem<Rect, float, float>( Shapes::RECT );
	theFactory.RegisterItem<Rect>( Shapes::RECT );

	std::vector< std::unique_ptr<Shape> > shapes;
	shapes.reserve( 16 );

	shapes.push_back( std::move( theFactory.Create( Shapes::CIRCLE, 2.f ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::CIRCLE, 1 ) ) );
    shapes.push_back( std::move( theFactory.Create( Shapes::CIRCLE ) ) );
    
    shapes.push_back( std::move( theFactory.Create( Shapes::RECT, 3.f, 4.f ) ) );    
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT, 1 ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT ) ) );
	shapes.push_back( std::move( theFactory.Create( Shapes::RECT, 9.f, 10.f ) ) );
	
	std::cout << std::fixed << std::setprecision( 2 );

	for( auto const & shape : shapes ) 
		std::cout << shape << std::endl;

	return 0;
}