#include <typeindex>
 
template <typename TFx, typename UFx, typename T>
    T maybe( bool isthere, T op,
		TFx&& fx = [ ] ( const T& x ) -> T { return x; },
		UFx&& defaultgen = [ ] ( ) -> T { return T( ); } ) {
		if ( isthere )
			return fx( op );
		return defaultgen( );
	}
 
int main() {
    
    int getone = maybe( true, 1 );
}