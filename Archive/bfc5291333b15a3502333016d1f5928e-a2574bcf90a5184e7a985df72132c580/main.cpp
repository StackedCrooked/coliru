#include <type_traits>
#include <iostream>
#include <tuple>

template<typename TFuncSignature>
struct function_traits;

template <class T, class R, class... Args> 
struct function_traits<R (T::*)(Args...)> {
	const static std::size_t arity = sizeof...( Args );
	using return_type = R;
	template <std::size_t I>
	using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	using func_pointer_type = R (T::*)(Args...);
};

template <class T, class R, class... Args> 
struct function_traits<R (*T::*)(Args...)> {
const static std::size_t arity = sizeof...( Args );
	using return_type = R;
	template <std::size_t I>
	using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	using func_pointer_type = R (T::*)(Args...);
};

template <class R, class... Args> 
struct function_traits<R (Args...)> {
	const static std::size_t arity = sizeof...( Args );
	using return_type = R;
	template <std::size_t I>
	using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	using func_pointer_type = R (*)(Args...);
};

template <class R, class... Args> 
struct function_traits<R (*)(Args...)> {
	const static std::size_t arity = sizeof...( Args );
	using return_type = R;
	template <std::size_t I>
	using arg_type = std::tuple_element<I, std::tuple<Args...>>;
	using func_pointer_type = R (*)(Args...);
};

template <typename TFunc, typename T = unsigned int, unsigned arity = function_traits<TFunc>::arity>
struct glDeleter;

template <typename TFunc, typename T>
struct glDeleter<TFunc, T, 1> {
    TFunc func;
    
    glDeleter( TFunc fx = TFunc() ) : func(fx) {
        
    }
};

template <typename TFunc, typename T>
struct glDeleter<TFunc, T, 2> {
    unsigned int size;
    TFunc func;
    
    glDeleter( unsigned int sz = 1, TFunc fx = TFunc() ) : size(sz), func(fx) {
        
    }
};


typedef unsigned int GLuint;

void glDeleteShader( GLuint id ) {
    
}

void glDeleteShaders( unsigned int size, GLuint id ) {
    
}

int main ( int argc, char* argv[] ) {
    
    glDeleter<decltype(&glDeleteShader)> delete1;
    glDeleter<decltype(&glDeleteShaders)> delete2( 5 );
    
    // not-possible
    //std::cout << delete1.size << std::endl;
    std::cout << delete2.size << std::endl;
    
}