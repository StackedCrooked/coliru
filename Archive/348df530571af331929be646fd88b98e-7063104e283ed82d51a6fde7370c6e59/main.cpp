#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <boost/any.hpp>
#include <memory>

#define furrovinememberapi
typedef std::size_t ulword;
const auto null = nullptr;

    template <typename T> 
	std::type_index typeof ( ) {
		return std::type_index( typeid( T ) );
	}

    class AnyServiceProvider {
	private:
		std::unordered_map<std::type_index, boost::any> services;

		furrovinememberapi AnyServiceProvider ( const AnyServiceProvider& nocopy );

	public:
		furrovinememberapi AnyServiceProvider ();

		furrovinememberapi AnyServiceProvider ( AnyServiceProvider&& mov );

		furrovinememberapi AnyServiceProvider( ulword initialcapacity );

		template <typename T> 
		bool TryGetService ( T*& service );

		template <typename T> 
		T* TryGetService ( );

		template <typename T>
		bool AddService ( const T& service );

		template <typename T>
		bool AddService ( T* service );

		template <typename T>
		bool AddService ( const T* service );

		template <typename T> 
		bool ReplaceService ( T* service, T*& old );

		template <typename T> 
		T& GetService ( );

		template <typename T> 
		T* GetServicePtr ( );

		template <typename T> 
		bool ContainsService ( );

		template <typename T> 
		bool RemoveService ( );

	};

    template <typename T>
	bool AnyServiceProvider::RemoveService( ) {
		return services.erase( typeof<T>() ) != services.end();
	}

	template <typename T>
	bool AnyServiceProvider::ContainsService( ) {
		return services.find( typeof<T>() ) != services.end();
	}

	template <typename T>
	T& AnyServiceProvider::GetService() {
		return *GetServicePtr<T>();
	}

	template <typename T>
	T* AnyServiceProvider::GetServicePtr() {
		auto p = services.find( typeof<T>() );
		if ( p == services.end() )
			throw "Fuck";

		return static_cast<T*>( boost::any_cast<T*>( p->second ) );
	}

	template <typename T>
	bool AnyServiceProvider::ReplaceService( T* service, T*& old ) {
		bool replaced = false;
		auto s = services.find( typeof<T>() );
		if ( s != services.end() ) {
			old = boost::any_cast<T*>( s->second );
			services.erase( s );
			replaced = true;
		}
		services.emplace( typeof( service ), boost::any( service ) );
		return replaced;
	}

	template <typename T>
	bool AnyServiceProvider::TryGetService( T*& service ) {
		auto s = services.find( typeof<T>() );
		if ( s == services.end() )
			return false;

		service = boost::any_cast<T*>( s->second );
		return true;
	}

	template <typename T>
	T* AnyServiceProvider::TryGetService( ) {
		T* service = null;
		TryGetService( service );
		return service;
	}

	template <typename T>
	bool AnyServiceProvider::AddService( const T& service ) {
		return AddService( const_cast<T*>( &service ) );
	}

	template <typename T>
	bool AnyServiceProvider::AddService( T* service ) {
		auto s = services.find( typeof<T>() );
		if ( s != services.end() ) {
			return false;
		}

		services.emplace_hint( s, typeof<T>(), boost::any( service ) );
		return true;
	}

	template <typename T>
	bool AnyServiceProvider::AddService( const T* service ) {
		return AddService( const_cast<T*>( service ) );
	}

    AnyServiceProvider::AnyServiceProvider( const AnyServiceProvider& nocopy ) {

	}

	AnyServiceProvider::AnyServiceProvider( AnyServiceProvider&& mov ) : services( std::move( mov.services ) ) {

	}

	AnyServiceProvider::AnyServiceProvider( ulword initialcapacity ) : services( initialcapacity ) {

	}

	AnyServiceProvider::AnyServiceProvider() : services( 8 ) {

	}

int main() {
    AnyServiceProvider provider;
    int* ptr = new int( 2 );
	provider.AddService( ptr );
	int& a = provider.GetService<int>();
	
	std::cout << a << std::endl;
	
	delete ptr;
}