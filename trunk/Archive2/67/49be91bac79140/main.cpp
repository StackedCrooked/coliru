#include <list>
#include <functional>

    template <typename... Tn> 
    class EventCaller;
	

    template <typename... Tn> 
	class Event {
	public:
        friend EventCaller<Tn...>;
		typedef void( *TPointerSignature )( Tn... );
		typedef void( TFunctionSignature )( Tn... );
		typedef std::function<TFunctionSignature> TCallback;
		typedef std::list<TCallback> InvocationTable;
		typedef typename InvocationTable::iterator Token;

	private:
		InvocationTable invocations;

	public:
		
		Event( ) : invocations( ) {
		
		}

		template <void ( *TFunc )( Tn... )> 
		Token Add( ) {
			TCallback c = TFunc;
			return Add( std::move( c ) );
		}

		template <typename T, void ( T::* TFunc )( Tn... )> 
		Token Add( T& object ) {
			return Add( std::addressof( object ) );
		}

		template <typename T, void ( T::* TFunc )( Tn... ) const>
		Token Add( T& object ) {
			return Add<T, TFunc>( std::addressof( object ) );
		}
		
		template <typename T, void ( T::* TFunc )( Tn... )>
		Token Add( T* object ) {
			TCallback c = std::bind( object, TFunc );
			return Add( std::move( c ) );
		}

		template <typename T, void ( T::* TFunc )( Tn... ) const> 
		Token Add( T* object ) {
			TCallback c = std::bind( object, TFunc );
			return Add( std::move( c ) );
		}

		Token Add( const TCallback& c ) {
			invocations.emplace_back( c );
			return --invocations.end( );
		}

		Token Add( TCallback&& c ) {
			invocations.emplace_back( std::move( c ) );
			return --invocations.end( );
		}

    private:
		template <typename... TArgn>
		void operator( )( TArgn&&... argn ) {
			Invoke( std::forward<TArgn>( argn )... );
		}

		template <typename... TArgn>
		void Invoke( TArgn&&... argn ) {
			static_assert( sizeof...( TArgn ) == sizeof...( Tn ), "Event must be called with the right amount of parameters." );
			for ( auto& invocation : invocations ) 
				invocation( std::forward<TArgn>( argn )... );
		}
        
    public:
		std::size_t InvocationCount( ) const {
			return invocations.size( );
		}

		bool Remove( const Token& token ) {
			invocations.erase( token ); return true;
		}

		template <typename TFx>
		Token operator += ( TFx&& fx ) {
			TCallback c = std::forward<TFx>( fx );
			return Add( std::move( c ) );
		}

		bool operator -= ( const Token& token ) {
			return Remove( token );
		}

		explicit operator bool( ) const {
			return InvocationCount( ) > 0;
		}
	};

    template <typename... Tn>
    class EventCaller {
    private:
        typedef Event<Tn...> TEvent;
        TEvent& event;
        
    public:
        
        EventCaller( TEvent& ev ) : event( ev ) {
            
        }
        
        template <typename... TArgn>
        void operator( )( TArgn&&... argn ) {
			event( std::forward<TArgn>( argn )... );
		}

		template <typename... TArgn>
		void Invoke( TArgn&&... argn ) {
			event.Invoke( std::forward<TArgn>( argn )... );
		}
        
    };
    
struct Arf {
private:
    int woofs = 0xF;
    EventCaller<int> woofcaller = Woof;
    
public:
     Event<int> Woof;

    void MakeWoof () {
        woofcaller( woofs );
        ++woofs;
    }

};

#include <iostream>

int main () {
    std::cout << std::hex;
    Arf a;
    a.Woof += []( int woofs ){ std::cout << woofs << std::endl; };
    // Prevent this line from compiling
    a.Woof( 0xBADCA11 ); 
    // This must compile
    a.MakeWoof();
}