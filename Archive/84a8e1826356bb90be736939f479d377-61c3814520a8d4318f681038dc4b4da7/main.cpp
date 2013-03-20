#include <list>
#include <functional>
#include <utility>

    template <typename T0, typename T1> 
    class Event2 {
	public:
		typedef void(* TPointerSignature)(T0, T1);
		typedef void( TFunctionSignature)(T0, T1);
		typedef std::function<TFunctionSignature> TCallback;
		typedef std::list<TCallback> InvocationTable;
		typedef typename InvocationTable::iterator Token;

	protected:
		InvocationTable invocations;

	public:
		Event2 () : invocations() {

		}

		template <void (* TFunc)(T0, T1)> 
		Token Add (  ) {
			TCallback c = TFunc;
			return Add( c );
		}

		template <typename T, void (T::* TFunc)(T0, T1)> 
		Token Add ( T& object ) {
			return Add<T, TFunc>( &object );
		}

		template <typename T, void (T::* TFunc)(T0, T1)> 
		Token Add ( T* object ) {
			TCallback c = std::bind( object, TFunc, std::placeholders::_1, std::placeholders::_2 );
			return Add( c );
		}

		template <typename T, void (T::* TFunc)(T0, T1) const> 
		Token Add ( T& object ) {
			return Add<T, TFunc>( &object );
		}

		template <typename T, void (T::* TFunc)(T0, T1) const> 
		Token Add ( T* object ) {
			TCallback c = std::bind( object, TFunc, std::placeholders::_1, std::placeholders::_2 );
			return Add( c );
		}

		Token Add ( TCallback&& c ) {
			invocations.push_back( c );
			return --invocations.end();
		}

		void Invoke ( T0&& t0, T1&& t1 ) {
			for ( auto& invocation : invocations ) {
				invocation( std::forward<T1>( t0 ), std::forward<T1>( t1 ) );
			}
		}

		void operator() ( T0&& t0, T1&& t1 ) {
			Invoke( std::forward<T0>( t0 ), std::forward<T1>( t1 ) );
		}

		operator bool () {
			return InvocationCount() > 0;
		}

		std::size_t InvocationCount ( ) {
			return invocations.size( );
		}

		bool Remove ( const Token& token )          
		{ invocations.erase( token ); return true; } 

	};

struct MyBigAssStruct {
    long long big1;
    long long big2;
    long long big3;
}

int main() {
    
    Event2<MyBigAssStruct, int> Doodeedoo;
    MyBigAssStruct s;
    Doodeedoo( s, 0 );
    
}