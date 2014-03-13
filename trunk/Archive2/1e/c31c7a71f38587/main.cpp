#include <utility>

template <typename TFx>
struct scoped_destructor {
	TFx fx;

	template <typename TFunc>
	scoped_destructor( TFunc&& func ) : fx( std::forward<TFunc>( func ) ) {

	}

	scoped_destructor( scoped_destructor&& mov ) : fx( std::move( mov.fx ) ) {

	}
	scoped_destructor& operator=( scoped_destructor&& mov ) { 
		fx = std::move( mov.fx ); 
	}
	
	~scoped_destructor( ) {
		fx( );
	}

};


template <typename TFx>
scoped_destructor<TFx> make_destructor( TFx&& fx ) {
	return scoped_destructor<TFx>( std::forward<TFx>( fx ) );
}

int main () {
    
}