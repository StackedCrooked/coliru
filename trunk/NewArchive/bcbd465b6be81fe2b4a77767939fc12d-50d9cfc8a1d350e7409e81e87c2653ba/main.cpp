#include <thread>
#include <vector>
#include <atomic>
#include <memory>
#include <iostream>

    template<typename TFuncSignature>
	struct function_traits;

	/*template <class R, class... Args> 
	struct function_traits<R (Args...)>{
		using result_type = R;
		const static std::size_t arity = sizeof...( Args );
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	};

	template <class R, class... Args> 
	struct function_traits<R (*)(Args...)>{
		using result_type = R;
		const static std::size_t arity = sizeof...( Args );
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	};*/

	template<typename R>
	struct function_traits<R ()> {
	
		typedef R return_type;
		typedef R (*func_type)( );
		const static std::size_t arity = 0;

	};

	template<typename R>
	struct function_traits<R (*)()> {

		typedef R return_type;
		typedef R (*func_type)( );
		const static std::size_t arity = 0;

	};

	template <>
	struct function_traits<void ()> {

		typedef void return_type;
		typedef void (*func_type)( );
		const static std::size_t arity = 0;

	};

	template <>
	struct function_traits<void  (*)()> {

		typedef void return_type;
		typedef void (*func_type)( );
		const static std::size_t arity = 0;

	};

	template<typename R, typename T0>
	struct function_traits<R ( T0 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef R (*func_type)( T0 );
		const static std::size_t arity = 1;

	};

	template<typename R, typename T0>
	struct function_traits<R (*)( T0 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef R (*func_type)( T0 );
		const static std::size_t arity = 1;

	};

	template<typename R, typename T0, typename T1>
	struct function_traits<R ( T0, T1 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef R (*func_type)( T0, T1 );
		const static std::size_t arity = 2;

	};

	template<typename R, typename T0, typename T1>
	struct function_traits<R (*)( T0, T1 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef R (*func_type)( T0, T1 );
		const static std::size_t arity = 2;

	};

	template<typename R, typename T0, typename T1, typename T2>
	struct function_traits<R ( T0, T1, T2 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef R (*func_type)( T0, T1, T2 );
		const static std::size_t arity = 3;

	};

	template<typename R, typename T0, typename T1, typename T2>
	struct function_traits<R (*)( T0, T1, T2 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef R (*func_type)( T0, T1, T2 );
		const static std::size_t arity = 3;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3>
	struct function_traits<R ( T0, T1, T2, T3 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef R (*func_type)( T0, T1, T2, T3 );
		const static std::size_t arity = 4;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3>
	struct function_traits<R (*)( T0, T1, T2, T3 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef R (*func_type)( T0, T1, T2, T3 );
		const static std::size_t arity = 4;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
	struct function_traits<R ( T0, T1, T2, T3, T4 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef T4 arg4_type;
		typedef R (*func_type)( T0, T1, T2, T3, T4 );
		const static std::size_t arity = 5;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4>
	struct function_traits<R (*)( T0, T1, T2, T3, T4 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef T4 arg4_type;
		typedef R (*func_type)( T0, T1, T2, T3, T4 );
		const static std::size_t arity = 5;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	struct function_traits<R ( T0, T1, T2, T3, T4, T5 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef T4 arg4_type;
		typedef T5 arg5_type;
		typedef R (*func_type)( T0, T1, T2, T3, T4, T5 );
		const static std::size_t arity = 6;

	};

	template<typename R, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
	struct function_traits<R (*)( T0, T1, T2, T3, T4, T5 )> {
	
		typedef R return_type;
		typedef T0 arg0_type;
		typedef T1 arg1_type;
		typedef T2 arg2_type;
		typedef T3 arg3_type;
		typedef T4 arg4_type;
		typedef T5 arg5_type;
		typedef R (*func_type)( T0, T1, T2, T3, T4, T5 );
		const static std::size_t arity = 6;

	};

/*template<unsigned...> struct indices{};

template<unsigned N, unsigned... Is>
struct indices_gen : indices_gen<N-1, N-1, Is...>{};

template<unsigned... Is>
struct indices_gen<0, Is...> : indices<Is...>{};

class Thread {
private:
    struct ThreadJumpBase {
        void operator() () const { Invoke(); }
        virtual void Invoke () const { }
        virtual ~ThreadJumpBase () {}
    };
    
    template <typename R, typename ...T>
    struct ThreadJump : public ThreadJumpBase {
        std::function<R( T... )> fx;
        std::tuple<T...> args;
        
        template <typename Fx, typename ...Tx>
        ThreadJump ( Fx&& f, Tx&&... params ) : fx( f ), args( std::forward<Tx>( params )... ) {
            
        }
        
        virtual void Invoke () const override {
            Invoke( indices_gen<sizeof...(T)>() );
        }
        
        template <unsigned ... I>
        void Invoke ( indices<I...> ) const {
            fx( std::move( std::get<I>( args ) )... );
        }
    };
    
    std::unique_ptr<ThreadJumpBase> threadjump;
    std::atomic<bool> done;
    std::thread thread;
    
public:

    template <typename Fx, typename ...T>
    Thread ( Fx&& fx, T&&... args ) : 
    threadjump( new ThreadJump<void, T...>( fx, std::forward<T>( args )... ) ), 
    done( false ), 
    thread( [&](){ (*threadjump)(); done = true; } ) {
    
    }
    
    bool Done () const {
        return done;
    }
    
    void Join () {
        thread.join();
    }
    
    ~Thread () {
        thread.join();
    }
};*/

void abc ( int val ) {
    std::cout << val << std::endl;
}

int main () {
    
    auto lamb = [] ( int val ) { abc(val); };
    function_traits< (decltype(lamb)) >::arg0_type v = 5;
    
    lamb(4);
    std::cout << v << std::endl;
    
    /*Thread t(lamb, 1);
    t.Join();
    while ( !t.Done() ) {
        std::cout << "Still not done..." << std::endl;
    }
    
    std::cout << 2 << std::endl;*/
}
