#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <memory>
#include <typeindex>

template < typename Key, typename Object >
class Factory{
private:
    using FakeCreatorFunc = Object* ( *)( );

    using RealKey    = std::pair< Key, std::type_index >;
	using CreatorMap = std::map<RealKey, FakeCreatorFunc>;
	
    template <typename T, typename... args>
    static Object * createFunc( args... arguments ) {
		return new T ( std::forward<args>( arguments )... );
	}
    
    CreatorMap creators_;

public:
	template < typename T, typename... args >
	typename std::enable_if< std::is_base_of<Object, T>::value &&
	std::is_constructible<T, args...>::value, bool >::type registerItem( Key key ) {
		using RealCreatorFunc = Object*  ( *)( args... );
		
        RealKey realKey { key, std::type_index( typeid( RealCreatorFunc ) ) };
        auto it = creators_.find( realKey );
		if ( it != creators_.end( ) )
			return false;
		creators_[ realKey ] = reinterpret_cast<FakeCreatorFunc>( createFunc<T, args...> );
		return true;
	}

	template < typename... args >
	std::unique_ptr<Object> create( Key key, args... arguments ) {
		using RealCreatorFunc = Object*  ( *)( args... );
		
        RealKey realKey { key, std::type_index( typeid( RealCreatorFunc ) ) };
		auto it = creators_.find( realKey );
		if ( it == creators_.end( ) )
			return {};
		auto creator = reinterpret_cast<RealCreatorFunc>( it->second );
		return std::unique_ptr<Object> { creator( std::forward<args>( arguments )... ) };
	}
};

struct Shape {
	virtual ~Shape( ) {}
    virtual void Display() const = 0;
protected:
	Shape( ) {}
};

struct Circle : public Shape {
	Circle( ) = default;
	Circle( float rad ) : radius_ { rad } {}	
    void Display() const override { std::cout << "Circle ( " << radius_ << " )"; }
private:
    float radius_ = 1.f;
};

struct Rect : public Shape {
	Rect( ) = default;
	Rect( float w, float h ) : w_ { w }, h_ { h } {}
    void Display() const override { std::cout << "Rect ( " << w_ << " x " << h_ << " )"; }
private:
    float w_ = 5.f;
    float h_ = 5.f;
};


Factory< std::string, Shape > theFactory;

int main( )
{
	theFactory.registerItem<Circle, float>( "Circle" );
	theFactory.registerItem<Rect, float, float>( "Rect" );
	theFactory.registerItem<Rect>( "Rect" );

	auto shape01 = theFactory.create( "Circle", 2.f );
	auto shape02 = theFactory.create( "Circle", 1 );
	auto shape03 = theFactory.create( "Rect", 1 );
	auto shape04 = theFactory.create( "Rect", 1.f, 2.f );
	auto shape05 = theFactory.create( "Rect" );

    auto DisplayShape = [] ( Shape const * shp ) {
        if ( shp ) {
            shp->Display();
            std::cout << std::endl;
        }
        else
            std::cout << "Empty shape" << std::endl;
    };

    std::cout.precision( 2 ); std::cout << std::fixed;
	DisplayShape( shape01.get() );
    DisplayShape( shape02.get() );
    DisplayShape( shape03.get() );
    DisplayShape( shape04.get() );
    DisplayShape( shape05.get() );

    return 0;
}