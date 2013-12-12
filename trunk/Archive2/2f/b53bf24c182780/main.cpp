#include <memory>
#include <iostream>
#include <tuple>
#include <type_traits>

    typedef std::size_t ulword;
    
    template<typename T>
    struct unqualified {
		typedef typename std::remove_cv< typename std::remove_reference<T>::type>::type type;
	};

    template <ulword... I> 
    struct indices_list { typedef indices_list type; };

	template <ulword N, ulword... I>
	struct make_indices : public make_indices<N - 1, N - 1, I...> { };

	template <ulword... I>
	struct make_indices<0, I...> : public indices_list<I...>{ };

	template <typename... Tn>
	struct types : make_indices<sizeof...( Tn )> { };

	template <typename T>
	struct tuple_indices : public make_indices<std::tuple_size<typename unqualified<T>::type>::value> { };

	template <typename... Tn>
	struct tuple_types : types<Tn...>, std::false_type { };

	template <typename... Tn>
	struct tuple_types<std::tuple<Tn...>> : types<Tn...>, std::true_type{ };

    template<typename TFuncSignature>
    struct function_traits;

	template<typename T, typename R, typename... Tn>
	struct function_traits<R( T::* )( Tn... )> {
		static const std::size_t arity = sizeof...( Tn );
		static const bool is_member_function = true;
		typedef std::tuple<Tn...> arg_tuple_t;
		typedef types<Tn...> args_t;
		typedef R( T::* func_t )( Tn... );
		typedef R( T::* func_pointer_t )( Tn... );
		typedef R return_t;
		template <std::size_t i>
		using arg_n = std::tuple_element<i, arg_tuple_t>;
	};

	template<typename T, typename R, typename... Tn>
	struct function_traits<R( T::* )( Tn... ) const> {
		static const std::size_t arity = sizeof...( Tn );
		static const bool is_member_function = true;
		typedef std::tuple<Tn...> arg_tuple_t;
		typedef types<Tn...> args_t;
		typedef R( T::* func_t )( Tn... );
		typedef R( T::* func_pointer_t )( Tn... );
		typedef R return_t;
		template <std::size_t i>
		using arg_n = std::tuple_element<i, arg_tuple_t>;
	};

	template<typename R, typename... Tn>
	struct function_traits<R( Tn... )> {
		static const std::size_t arity = sizeof...( Tn );
		static const bool is_member_function = false;
		typedef std::tuple<Tn...> arg_tuple_t;
		typedef types<Tn...> args_t;
		typedef R( func_t )( Tn... );
		typedef R( *func_pointer_t )( Tn... );
		typedef R return_t;
		template <std::size_t i>
		using arg_n = std::tuple_element<i, arg_tuple_t>;
	};

	template<typename R, typename... Tn>
	struct function_traits<R( *)( Tn... )> {
		static const std::size_t arity = sizeof...( Tn );
		static const bool is_member_function = false;
		typedef std::tuple<Tn...> arg_tuple_t;
		typedef types<Tn...> args_t;
		typedef R( func_t )( Tn... );
		typedef R( *func_pointer_t )( Tn... );
		typedef R return_t;
		template <std::size_t i>
		using arg_n = std::tuple_element<i, arg_tuple_t>;
	};

class Class {};
void f();

static_assert(function_traits<void (Class::*)()>::is_member_function, "");
static_assert(!function_traits<decltype(&f)>::is_member_function, "");
static_assert(function_traits<int (Class::*)>::is_member_function , "");

int main() {
    std::cout << "<3 Xeo <3" << std::endl;
}