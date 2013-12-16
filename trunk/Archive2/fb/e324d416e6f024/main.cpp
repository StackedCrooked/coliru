#include <type_traits>
#include <new>
#include <utility>
#include <vector>
#include <functional>
#include <algorithm>

const auto null = nullptr;
#define inlinealways inline

template<typename TFuncSignature>
class Callback;


template <typename R, typename... Tn>
class Callback<R(Tn...)> {
public:
	static const std::size_t Arity = sizeof... ( Tn );
	typedef R(*TFunc)(void*, Tn...);

	Callback() : obj(null), func(null) {}
	Callback(void* o, TFunc f) : obj(o), func(f) {}
	Callback(std::function<R (Tn...)> f) : obj(null), func(f.target<R(Tn...)>()) {}

	R operator()(Tn... a) const {
		return (*func)(obj, a...);
	}

	explicit operator bool () const {
		return func ? true : false;
	}

	bool operator!() const {
		return func == 0;
	}
	bool operator== (const Callback<R (Tn...)>& right) const {
		return obj == right.obj && func == right.func;
	}
	bool operator!= (const Callback<R (Tn...)>& right) const {
		return obj != right.obj || func != right.func;
	}
private:
	void* obj;
	TFunc func;
};

namespace detail {
	template <typename R, typename T, typename... Tn>
	struct DeduceCallback { 
		template <R(T::*Func)( Tn... )> 
		inlinealways static Callback<R( Tn... )> Bind(T* o) {
			struct _ { static R wrapper(void* o, Tn... a) { return (static_cast<T*>(o)->*Func)(a...); } };
			return Callback<R( Tn... )>(o, (R(*)(void*, Tn...)) _::wrapper);
		}

		template <R( T::*Func )( Tn... ) const>
		inlinealways static Callback<R( Tn... )> Bind( T* o ) {
			struct _ { static R wrapper( void* o, Tn... a ) { return ( static_cast<T*>( o )->*Func )( a... ); } };
			return Callback<R( Tn... )>( o, ( R( *)( void*, Tn... ) ) _::wrapper );
		}
	};

	template<typename R, typename... Tn>
	struct DeduceStaticCallback { 
		template <R(*Func) (Tn... )> 
		inlinealways static Callback<R(Tn...)> Bind() { 
			struct _ { static R wrapper(void*, Tn... a) { return (*Func)(a...); } };
			return Callback<R(Tn...)>(0, (R(*)(void*, Tn...)) _::wrapper); 
		}
	};
}

template<typename R, class T, typename... Tn>
detail::DeduceCallback<R, T, Tn...> DeduceCallback(R(T::*)(Tn...)) {
	return detail::DeduceCallback<R, T, Tn...>();
}

template<typename R, class T, typename... Tn>
detail::DeduceCallback<R, T, Tn...> DeduceCallback(R(T::*)(Tn...) const) {
	return detail::DeduceCallback<R, T, Tn...>();
}

template<typename R, typename... Tn>
detail::DeduceCallback<R, Tn...> DeduceCallback(R(*)(Tn...)) {
	return detail::DeduceStaticCallback<R, Tn...>();
}

template <typename... Tn> 
class CallbackEvent {
public:
	typedef void(*TFunctionSignature)(Tn...);
	typedef Callback<void(Tn...)> TCallback;
	typedef std::vector<TCallback> InvocationTable;

protected:
	InvocationTable invocations;

public:
	static const std::size_t DefaultFunctorCapacity = 4;

	CallbackEvent() : invocations() {
		invocations.reserve(DefaultFunctorCapacity);
	}

	template <void (* TFunc)(Tn...)>
	void Add() {
		TCallback c = DeduceCallback(TFunc).template Bind<TFunc>();
		invocations.push_back(c);
	}

	template <typename T, void (T::* TFunc)(Tn...)>
	void Add(T& object) {
		Add<T, TFunc>(&object);
	}

	template <typename T, void (T::* TFunc)(Tn...)>
	void Add(T* object) {
		TCallback c = DeduceCallback(TFunc).template Bind<TFunc>(object);
		invocations.push_back(c);
	}

	template <typename T, void (T::* TFunc)(Tn...) const>
	void Add(T& object) {
		Add<T, TFunc>(&object);
	}

	template <typename T, void (T::* TFunc)(Tn...) const> 
	void Add(T* object) {
		TCallback c = DeduceCallback(TFunc).template Bind<TFunc>(object);
		invocations.push_back(c);
	}

	template <typename... TArgn>
	void Invoke( TArgn&&... a ) {
		for(size_t i = 0; i < invocations.size() ; ++i) invocations[i]( std::forward<Tn>( a )... ); 
	}
	
	template <typename... TArgn>
	void operator()( TArgn&&... a ) {
		Invoke( std::forward<Tn>( a )... );
	}

	std::size_t InvocationCount() { return invocations.size(); }

	template <void (* TFunc)(Tn...)> 
	bool Remove () { return Remove (DeduceCallback(TFunc).template Bind<TFunc>()); } 

	template <typename T, void (T::* TFunc)(Tn...)> 
	bool Remove (T& object) { return Remove <T, TFunc>(&object); } 
	
	template <typename T, void (T::* TFunc)(Tn...)> 
	bool Remove (T* object) { return Remove (DeduceCallback(TFunc).template Bind<TFunc>(object)); } 
	
	template <typename T, void (T::* TFunc)(Tn...) const> 
	bool Remove (T& object) { return Remove <T, TFunc>(&object); } 
	
	template <typename T, void (T::* TFunc)(Tn...) const> 
	bool Remove (T* object) { return Remove (DeduceCallback(TFunc).template Bind<TFunc>(object)); } 

protected:
	bool Remove( TCallback const& target ) {
		auto it = std::find(invocations.begin(), invocations.end(), target);
		if (it == invocations.end()) 
			return false;
		invocations.erase(it);
		return true;
	}
};


int main() {
    
}

