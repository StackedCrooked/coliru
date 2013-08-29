template <typename T0> class CallbackEvent1 {
public:
	typedef void(* TFunctionPointerSignature)(T0);
	typedef void( TFunctionSignature)(T0);
	typedef Callback<void(T0)> TCallback;
	typedef std::vector<TCallback> InvocationTable;

protected:
	InvocationTable invocations;

public:
	/* BLAH BLAH BLAH FUN SHIT */

    // Of the below,
    // Which ones do I need? The raw one, and then the Forwarding one? Or the Do-Not-Copy one?

    // Raw Semantics
    void Invoke ( T0 t0 ) {
		std::size_t i;
		for ( i = 0; i < invocations.size(); ++i ) {
			invocations[i]( t0 );
		}
	}

    // Do-Not-Copy semantics
    void Invoke ( T0 const& t0 ) {
		std::size_t i;
		for ( i = 0; i < invocations.size(); ++i ) {
			invocations[i]( t0 );
		}
	}

    // Forward-Semantics
    void Invoke ( T0&& t0 ) {
		std::size_t i;
		for ( i = 0; i < invocations.size(); ++i ) {
			invocations[i]( std::forward<T0>( t0 ) );
		}
	}
}


int main (int, char*[] ) {
    
    
}