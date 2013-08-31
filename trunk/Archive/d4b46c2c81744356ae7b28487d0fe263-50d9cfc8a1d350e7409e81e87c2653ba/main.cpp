#include <thread>
#include <vector>
#include <atomic>
#include <memory>
#include <iostream>

    template<typename TFuncSignature>
	struct function_traits;

    template <class T, class R, class... Args> 
    struct function_traits<R (T::*)(Args...)> {
		const static std::size_t arity = sizeof...( Args );
		using return_type = R;
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
		using func_type = R (T::*)(Args...);
	};

	template <class T, class R, class... Args> 
	struct function_traits<R (*T::*)(Args...)> {
	const static std::size_t arity = sizeof...( Args );
		using return_type = R;
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
		using func_type = R (T::*)(Args...);
	};

	template <class R, class... Args> 
	struct function_traits<R (Args...)> {
		const static std::size_t arity = sizeof...( Args );
		using return_type = R;
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
		using func_type = R (*)(Args...);
	};

	template <class R, class... Args> 
	struct function_traits<R (*)(Args...)> {
		const static std::size_t arity = sizeof...( Args );
		using return_type = R;
		template <std::size_t I>
		using arg_type = std::tuple_element<I, std::tuple<Args...>>;
		using func_type = R (*)(Args...);
	};

template<unsigned...> struct indices{};

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
};

void abc ( int val ) {
    std::cout << val << std::endl;
}

struct abcfoo {
    void operator () ( int val ) { 
        abc(val); 
    }
};

template <typename T>
struct nullof {
    const static T* null;
};

template <typename T> 
const T* nullof<T>::null = (T*)nullptr;

template <typename T, typename TR, typename ...TArgs>
struct has_lambda_operator {
	typedef char yes[1];
	typedef char no[2];
	
	template<typename C, TR (C::*)( TArgs... ) const> struct SFINAE {};

	template <typename C>
	static yes& test(SFINAE<C, &C::operator()>*);

	template <typename>
	static no& test(...);

	static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

int main () {
    
    auto lamb = [] ( int val ) { abc(val); };
    
    typedef function_traits< decltype( &abcfoo::operator() ) >::arg_type<0>::type intabcfoo_t;
    intabcfoo_t intabcfoo = 5;
    lamb(intabcfoo);
    
    typedef function_traits< decltype( abc ) >::arg_type<0>::type intabc_t;
    intabc_t intabc = 4;
    lamb(intabc);
    
    std::cout << has_lambda_operator< decltype( lamb ), void, int >::value << std::endl;
    
    /*typedef decltype(lamb) lamb_t;
    typedef function_traits< decltype( lamb() ) >::arg0_type intlamb_t;
    intlamb_t intlamb = 5;
    lamb(intlamb);*/
    
    /*Thread t(lamb, 1);
    t.Join();
    while ( !t.Done() ) {
        std::cout << "Still not done..." << std::endl;
    }
    
    std::cout << 2 << std::endl;*/
}
