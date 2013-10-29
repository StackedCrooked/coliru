#define UTILS

#include <string>
#include <cxxabi.h>
#include <cstdlib>

template<typename T>
std::string type2str(const T& _t)
{
    char* name = abi::__cxa_demangle(typeid(T).name(), 0, 0, 0);
	std::string str{name};
	free(name);
	return str;
}

std::string operator"" _s(const char* _c, std::size_t)
{
	return _c;
}

#define TTRICKS

#include <iostream>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <functional>

template<typename T>
struct Is_Tuple_Base
{
	const static bool value{false};
};

template<typename... Ts>
struct Is_Tuple_Base<std::tuple<Ts...>>
{
	const static bool value{true};
};

template<typename T>
struct Is_Tuple : public Is_Tuple_Base<typename std::decay<T>::type>
{
// 	typedef typename std::conditional<Is_Tuple_Base::value, typename std::decay<T>::type, void>::type type;
};

template<typename T, typename...Ts>
std::tuple<T> head(const std::tuple<T, Ts...>& _t)
{
	return std::make_tuple(std::get<0>(_t));
}

template<int N, bool within, typename T, typename... Ts>
struct TTail
{
	// Tuple concatenation of tuple at element N and tuple of everything after element N
	typedef decltype(std::tuple_cat(std::make_tuple(std::get<N>(std::declval<std::tuple<T, Ts...>>())), std::declval<typename TTail<N+1, N+1 < sizeof...(Ts), T, Ts...>::type>())) type;

	// Parameter H is the final tail tuple type
	template<typename H>
	static H tail(const std::tuple<T, Ts...>& _t)
	{
		H _p = TTail<N+1, N+1 < sizeof...(Ts), T, Ts...>::template tail<H>(std::forward<decltype(_t)>(_t));
		// Element N, adjusted for size difference between _p and _t, of _p is element N of _t
		std::get<N-(sizeof...(Ts)-std::tuple_size<H>::value)-1>(_p) = std::get<N>(_t);
		return _p;
	}
};

template<int N, typename T, typename... Ts>
struct TTail<N, false, T, Ts...>
{
	// Tuple of the last element of Ts...
	typedef decltype(std::make_tuple(std::get<sizeof...(Ts)>(std::declval<std::tuple<T, Ts...>>()))) type;

	// Same as previous
	template<typename H>
	static H tail(const std::tuple<T, Ts...>& _t)
	{
		H _p;
		// Last element of _p is last element of _t
		std::get<std::tuple_size<H>::value-1>(_p) = std::get<sizeof...(Ts)>(_t);
		return _p;
	}
};

template<int N, typename T, typename... Ts>
typename TTail<N, N <= sizeof...(Ts), T, Ts...>::type tail(const std::tuple<T, Ts...>& _t)
{
	static_assert(N >= 0, "Will not create tail from [<0, end)");
	return TTail<N, N <= sizeof...(Ts), T, Ts...>::template tail<typename TTail<N, N <= sizeof...(Ts), T, Ts...>::type>(std::forward<decltype(_t)>(_t));
}

template<typename T, typename... Ts>
std::tuple<Ts...> tail(const std::tuple<T, Ts...>& _t)
{
	return tail<1>(std::forward<decltype(_t)>(_t));
}

template<typename T>
std::tuple<T> tail(const std::tuple<T>& _t)
{
	return _t;
}

/* There's a subtle bug with the TTail template class when dealing with 2-tuples.
 * So providing this specialization for 2-tuples.
 */
template<typename T, typename U>
std::tuple<U> tail(const std::tuple<T, U>& _t)
{
	return std::make_tuple(std::get<1>(_t));
}

template<int N, bool exceeded, typename T, typename... Ts>
struct THead
{
	// Tuple concatenation of head of <T, Ts...> and the N-1 elements after it
	typedef decltype(std::tuple_cat(std::declval<std::tuple<T>>(), std::declval<typename THead<N-1, exceeded, Ts...>::type>())) type;

	template<typename H>
	static H head(const std::tuple<T, Ts...>& _t)
	{
		H _h = THead<N-1, exceeded, T, Ts...>::template head<H>(std::forward<decltype(_t)>(_t));
		// Elements of _h and _t line up for the tuple size of H
		std::get<N>(_h) = std::get<N>(_t);
		return _h;
	}
};

template<bool exceeded, typename T, typename... Ts>
struct THead<0, exceeded, T, Ts...>
{
	typedef std::tuple<T> type;

	template<typename H>
	static H head(const std::tuple<T, Ts...>& _t)
	{
		H _h;
		std::get<0>(_h) = std::get<0>(_t);
		return _h;
	}
};

template<int N, typename T, typename... Ts>
struct THead<N, true, T, Ts...>
{
	typedef std::tuple<T, Ts...> type;

	template<typename H>
	static H head(const std::tuple<T, Ts...>& _t)
	{
		return THead<N-1, sizeof...(Ts) < N-1, T, Ts...>::template head<H>(std::forward<decltype(_t)>(_t));
	}
};

template<int N, typename T, typename... Ts>
typename THead<N-1, sizeof...(Ts) < N-1, T, Ts...>::type head(const std::tuple<T, Ts...>& _t)
{
	static_assert(N > 0, "Cannot create head from [0, 0)");
	return THead<N-1, sizeof...(Ts) < N-1, T, Ts...>::template head<typename THead<N-1, sizeof...(Ts) < N-1, T, Ts...>::type>(std::forward<decltype(_t)>(_t));
}

template<typename T>
struct TChoice
{
	template<typename U>
	static T choice(const T& _t, const U& _u)
	{
		return _t;
	}

	template<typename U>
	static T choice(const U& _u, const T& _t)
	{
		return _t;
	}
};

template<typename T, typename U>
struct TMin
{
	static_assert(Is_Tuple<T>::value, "TMin 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "TMin 2nd template argument is not a tuple");
	typedef typename std::conditional<std::tuple_size<T>::value < std::tuple_size<U>::value, T, U>::type type;
	typedef typename std::conditional<sizeof(T) < sizeof(U), T, U>::type stype;

	static type tmin(const T& _t, const U& _u)
	{
		return TChoice<type>::choice(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
	}

	static stype tsmin(const T& _t, const U& _u)
	{
		return TChoice<stype>::choice(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
	}
};

template<typename T, typename U>
struct TMax
{
	static_assert(Is_Tuple<T>::value, "TMax 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "TMax 2nd template argument is not a tuple");
	typedef typename std::conditional<std::tuple_size<U>::value < std::tuple_size<T>::value, T, U>::type type;
	typedef typename std::conditional<sizeof(U) < sizeof(T), T, U>::type stype;

	static type tmax(const T& _t, const U& _u)
	{
		return TChoice<type>::choice(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
	}

	static stype tsmax(const T& _t, const U& _u)
	{
		return TChoice<stype>::choice(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
	}
};

template<typename T, typename U>
typename TMin<T, U>::type tmin(const T& _t,  const U& _u)
{
	static_assert(Is_Tuple<T>::value, "tmin 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "tmin 2nd template argument is not a tuple");
	return TMin<T, U>::tmin(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
}

template<typename T, typename U>
typename TMax<T, U>::type tmax(const T& _t,  const U& _u)
{
	static_assert(Is_Tuple<T>::value, "tmax 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "tmax 2nd template argument is not a tuple");
	return TMax<T, U>::tmax(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
}

template<typename T, typename U>
typename TMin<T, U>::stype tsmin(const T& _t,  const U& _u)
{
	static_assert(Is_Tuple<T>::value, "tsmin 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "tsmin 2nd template argument is not a tuple");
	return TMin<T, U>::tsmin(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
}

template<typename T, typename U>
typename TMax<T, U>::stype tsmax(const T& _t,  const U& _u)
{
	static_assert(Is_Tuple<T>::value, "tsmax 1st template argument is not a tuple");
	static_assert(Is_Tuple<U>::value, "tsmax 2nd template argument is not a tuple");
	return TMax<T, U>::tsmax(std::forward<decltype(_t)>(_t), std::forward<decltype(_u)>(_u));
}

/* For tuple mapping functions that need to know where in a tuple an element is
 *
 */
enum class Element_Disp
{
	BEGIN,
	MIDDLE,
	END
};

/* Template class G specializes between elements of tuple and non tuple type
 * G has a function called map that takes the current element, an accumulator function, and the disposition of the element
 */
template<int N, template<bool> class G, typename... Ts>
struct TMap
{
	template<typename A>
	static void map(const std::tuple<Ts...>& _t, const std::function<void(A)>& _a)
	{
		TMap<N-1, G, Ts...>::map(std::forward<decltype(_t)>(_t), _a);
		typedef decltype(std::get<N>(_t)) Ntype;
		G<Is_Tuple<Ntype>::value>::map(std::forward<Ntype>(std::get<N>(_t)), _a, (N == sizeof...(Ts) - 1? Element_Disp::END : Element_Disp::MIDDLE));
	}
};

/* Specialize for when tuple enumeration has reached the first element
 *
 */
template<template<bool> class G, typename... Ts>
struct TMap<0, G, Ts...>
{
	template<typename A>
	static void map(const std::tuple<Ts...>& _t, const std::function<void(A)>& _a)
	{
		typedef decltype(std::get<0>(_t)) Ntype;
		G<Is_Tuple<Ntype>::value>::map(std::forward<Ntype>(std::get<0>(_t)), _a, Element_Disp::BEGIN);
	}
};

/* Specialization for a 1-tuple
 *
 */
template<template<bool> class G, typename T>
struct TMap<0, G, T>
{
	template<typename A>
	static void map(const std::tuple<T>& _t, const std::function<void(A)>& _a)
	{
		typedef decltype(std::get<0>(_t)) Ntype;
		G<Is_Tuple<Ntype>::value>::map(std::forward<Ntype>(std::get<0>(_t)), _a, Element_Disp::END);
	}
};

/* User provides template class G and an accumulator function
 * G must be specified explicitly tmap<G>(...)
 */
template<template<bool> class G, typename A, typename T, typename... Ts>
void tmap(const std::tuple<T, Ts...>& _t, const std::function<void(A)>& _a)
{
	TMap<sizeof...(Ts), G, T, Ts...>::map(std::forward<decltype(_t)>(_t), _a);
}

template<bool>
struct TMapPrint
{
	template<typename T>
	static void map(const T& _t, const std::function<void(std::string)>& _a, Element_Disp _d)
	{
		std::ostringstream strm;
		strm << _t << (_d != Element_Disp::END ? ", " : " ");
		_a(strm.str());
	}
};

template<>
struct TMapPrint<true>
{
	static int level;

	template<typename... Ts>
	static void map(const std::tuple<Ts...>& _t, const std::function<void(std::string)>& _a, Element_Disp _d)
	{
		level += 1;
		if(_d != Element_Disp::BEGIN)
		{
			_a(std::string("\n"));
			for(int l = 0; l < level - 1; ++l)
			{
				_a("| ");
			}
			if(level > 0)
			{
				_a("|_");
			}
		}
		_a("< ");
		tmap<TMapPrint>(_t, _a);
		_a(">");
		if(_d != Element_Disp::END)
		{
			_a(std::string(",\n"));
			for(int l = 0; l < level - 1; ++l)
			{
				_a("| ");
			}
			_a("|_");
		}
		else
		{
			_a(" ");
		}
		level -= 1;
	}
};

int TMapPrint<true>::level = -1;

template<typename... Ts>
std::ostream& operator<<(std::ostream& _out, const std::tuple<Ts...>& _t)
{
	std::string tupstr;
	TMapPrint<true>::map(_t, std::function<void(std::string)>([&tupstr](std::string _s)
	{
		if(tupstr.rfind("|_\n") == tupstr.size() - 3)
		{
			tupstr.pop_back();
			tupstr.erase(tupstr.rfind('\n') + 1);
		}
		tupstr.append(_s);
	}), Element_Disp::END);
	return _out << tupstr;
}

#define AST

#include <unordered_map>

/* Parse_Exceptions
 *
 * These codes are thrown during parsing to direct the path of AST
 */
enum class Parse_Exceptions
{
	PARSE_RULE_NO_DEF = 0,
	NUM_PARSE_EXCEPTIONS
};

std::ostream& operator<<( std::ostream& _out, Parse_Exceptions _e )
{
	static const char* PE_Enum2Str[static_cast<std::underlying_type<Parse_Exceptions>::type>(Parse_Exceptions::NUM_PARSE_EXCEPTIONS)] =
	{
		"Parse rule not defined"
	};

	return _out << PE_Enum2Str[static_cast<std::underlying_type<Parse_Exceptions>::type>(_e)];
}

/* TRef<N>
 *
 * This is a reference within an AST tuple.
 * Its presence in an AST tuple is not addressable by a TRef.
 */
template<int N>
struct TRef
{
	static const decltype(N) value{N};
};

template<int N>
std::ostream& operator<<(std::ostream& _out, TRef<N> _m)
{
	return _out << "@<" << N << ">";
}

/* TCondition<E>
 *
 * This is a marker in an AST tuple to instruct the parser to report a condition.
 * It is in the discretion of a parse rule to heed the condition.
 */
template<Parse_Exceptions E>
struct TCondition
{
	static const decltype(E) value{E};
};

template<Parse_Exceptions E>
struct TError : public TCondition<E>{};
template<Parse_Exceptions E>
struct TWarn : public TCondition<E>{};

template<Parse_Exceptions E>
std::ostream& operator<<(std::ostream& _out, TError<E> _e)
{
	return _out << "E<" << E << ">";
}

template<Parse_Exceptions E>
std::ostream& operator<<(std::ostream& _out, TWarn<E> _e)
{
	return _out << "W<" << E << ">";
}

typedef char* mmidx;
typedef std::tuple<mmidx, mmidx, size_t, size_t, size_t, size_t> token_type;	// Start, end, start line, start column, end line, end colum

enum class Rule_Types
{
	CHARSET,	// Character is a part of token character set
	KEYWORD,	// Character is in sequence of recognized keyword
	CONJUNCT,	// Adjacent tokens
	DISJUNCT,	// Try next choice if fail
	NEGATION,	// Fail if matches
	OPTIONAL,	// Token is not mandatory
	SUCCESS,	// Always succeessful
	FAILURE,	// Never successful
	CLARIFY,	// Re-evaluate match with more information
	DISSECT,	// Process tokens
	NUM_RULE_TYPES
};

template<Rule_Types R>
struct Rule_Wrapper
{
	const static Rule_Types value{R};
};

std::ostream& operator<<(std::ostream& _out, Rule_Types _r)
{
	static const char* RT_Enum2Str[static_cast<std::underlying_type<Rule_Types>::type>(Rule_Types::NUM_RULE_TYPES)] = {
		"Charset rule",
		"Keyword rule",
		"Conjunct rule",
		"Disjunct rule",
		"Negation rule",
		"Optional rule",
		"Success rule",
		"Failure rule",
		"Clarification rule",
		"Dissection rule"
	};

	return _out << RT_Enum2Str[static_cast<std::underlying_type<Rule_Types>::type>(_r)];
}

template<Rule_Types R>
std::ostream& operator<<(std::ostream& _out, Rule_Wrapper<R> _w)
{
	static const char* RT_Enum2Str[static_cast<std::underlying_type<Rule_Types>::type>(Rule_Types::NUM_RULE_TYPES)] = {
		"[",
		"=",
		"&",
		"|",
		"~",
		"?",
		"true",
		"false",
		"/",
		"%"
	};

	return _out << RT_Enum2Str[static_cast<std::underlying_type<Rule_Types>::type>(R)] << (R <= Rule_Types::DISJUNCT ? " =>" : "");
}

struct Rule
{
	std::function<token_type(mmidx)> read_fun;

	Rule& operator=( const decltype(read_fun)& _fun )
	{
		this->read_fun = _fun;
		return *this;
	}

	Rule& operator=( decltype(read_fun)&& _fun )
	{
		this->read_fun = std::move(_fun);
		return *this;
	}

	template<typename T>
	Rule& operator=(std::tuple<T>&& _t)
	{
		std::clog << "Sizeof tuple tail: " << 1 << " of " << type2str(_t) << std::endl;
		std::clog << std::forward<decltype(_t)>(_t) << std::endl;
		return *this;
	}

	template<typename T, typename... Ts>
	Rule& operator=(std::tuple<T, Ts...>&& _t)
	{
		std::clog << "Sizeof tuple tail: " << sizeof...(Ts) << " of " << type2str(_t)<< std::endl;
		std::clog << std::forward<decltype(_t)>(_t) << std::endl;
		return *this;
	}

	operator bool()
	{
		return static_cast<bool>(this->read_fun);
	}

	typename decltype(read_fun)::result_type operator()(typename decltype(read_fun)::argument_type _arg)
	{
		return this->read_fun(_arg);
	}
};

std::ostream& operator<<(std::ostream& _out, const Rule& _t)
{
	return _out << "Rule";
}

/*
template<typename... Ts>
Rule& operator&&= (Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}

template<typename... Ts>
Rule& operator||=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}

template<typename... Ts>
Rule& operator&=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}
template<typename... Ts>
Rule& operator|=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}

template<typename... Ts>
Rule& operator+=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}
template<typename... Ts>
Rule& operator-=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}

template<typename... Ts>
Rule& operator*=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}

template<typename... Ts>
Rule& operator/=(Rule& _r, const std::tuple<Ts...>& _t)
{
	std::clog << "Sizeof tuple: " << sizeof...(Ts) << std::endl;
	return _r;
}*/

template<Rule_Types J, typename T, typename U>
struct Rule_Operator;

/* Base case is to create a 3-tuple with Rule_Types as first element
 * The second and third elements are the tuples, forming a binary tree
 * eg: A & B | C => <|, <&, A, B>, C>
 */
template<Rule_Types J, Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
struct Rule_Operator<J, std::tuple<Rule_Wrapper<T>, Ts...>, std::tuple<Rule_Wrapper<U>, Us...>>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef std::tuple<Rule_Wrapper<T>, Ts...> left_type;
	typedef std::tuple<Rule_Wrapper<U>, Us...> right_type;
	typedef std::tuple<rule_type, left_type, right_type> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		return std::make_tuple(rule_type{}, _t, _u);
	}
};

/* Specialize for when the top level rule type is the same as the LHS
 * Thus concatenate the RHS to the LHS and use that as the rule
 * eg: (A & B) & C => A & B & C => <&, A, B, C>
 */
template<Rule_Types J, Rule_Types U, typename... Ts, typename... Us>
struct Rule_Operator<J, std::tuple<Rule_Wrapper<J>, Ts...>, std::tuple<Rule_Wrapper<U>, Us...>>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef std::tuple<Rule_Wrapper<J>, Ts...> left_type;
	typedef std::tuple<Rule_Wrapper<U>, Us...> right_type;
	typedef std::tuple<rule_type, Ts..., right_type> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		return std::tuple_cat(std::make_tuple(rule_type{}), tail(_t), std::make_tuple(_u));
	}
};

template<Rule_Types J, typename U, typename... Ts>
struct Rule_Operator<J, std::tuple<Rule_Wrapper<J>, Ts...>, U>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef std::tuple<Rule_Wrapper<J>, Ts...> left_type;
	typedef U right_type;
	typedef std::tuple<rule_type, Ts..., right_type> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		std::clog <<  _u;
		return std::tuple_cat(std::make_tuple(rule_type{}), tail(_t), std::make_tuple(_u));
	}
};

/* Specialize for when the top level rule type is the same as the RHS
 * Thus concatenate the LHS to the LHS and use that as the rule
 * eg: A & (B & C) => A & B & C => <&, A, B, C>
 */
template<Rule_Types J, Rule_Types T, typename... Ts, typename... Us>
struct Rule_Operator<J, std::tuple<Rule_Wrapper<T>, Ts...>, std::tuple<Rule_Wrapper<J>, Us...>>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef std::tuple<Rule_Wrapper<T>, Ts...> left_type;
	typedef std::tuple<Rule_Wrapper<J>, Us...> right_type;
	typedef std::tuple<rule_type, left_type, Us...> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		return std::tuple_cat(std::make_tuple(rule_type{}), std::make_tuple(_t), tail(_u));
	}
};

template<Rule_Types J, typename T, typename... Us>
struct Rule_Operator<J, T, std::tuple<Rule_Wrapper<J>, Us...>>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef T left_type;
	typedef std::tuple<Rule_Wrapper<J>, Us...> right_type;
	typedef std::tuple<rule_type, left_type, Us...> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		return std::tuple_cat(std::make_tuple(rule_type{}), std::make_tuple(_t), tail(_u));
	}
};

/* Special case for a concatenation of equal rules is to create a tuple with Rule_Types as first element
 * The tail of the two tuples is then concatenated and appended with the new tuple
 * In effect, the combination of the previous two specializations
 * eg: A & B & C => <&, A, B, C> instead of <&, <&, A, B>, C>
 */
template<Rule_Types J, typename... Ts, typename... Us>
struct Rule_Operator<J, std::tuple<Rule_Wrapper<J>, Ts...>, std::tuple<Rule_Wrapper<J>, Us...>>
{
	typedef Rule_Wrapper<J> rule_type;
	typedef std::tuple<Rule_Wrapper<J>, Ts...> left_type;
	typedef std::tuple<Rule_Wrapper<J>, Us...> right_type;
	typedef std::tuple<rule_type, Ts..., Us...> result_type;
	static result_type op(const left_type& _t, const right_type& _u)
	{
		return std::tuple_cat(std::make_tuple(rule_type{}), tail(_t), tail(_u));
	}
};

/* OR-ing two charset patterns together is really just one big charset rule
 * eg: "abcdefg" | "hijklmn" => <{}, "abcdefghijklmn">
 */
template<typename T>
struct Rule_Operator<Rule_Types::DISJUNCT, std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, T>, std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, T>>
{
	typedef std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, T> result_type;
	static result_type op(const std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, T>& _t, const std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, T>& _u)
	{
		return std::make_tuple(Rule_Wrapper<Rule_Types::CHARSET>(), std::get<1>(_t) + std::get<1>(_u));
	}
};

/* Proxy templated types for rule combination
 * Restricts use to tuples with Rule_Wrapper<R> as element 0
 */
template<Rule_Types J, typename T, typename U = void>
struct Bound_Tuple;

template<Rule_Types J, Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
struct Bound_Tuple<J, std::tuple<Rule_Wrapper<T>, Ts...>, std::tuple<Rule_Wrapper<U>, Us...>>
{
	typedef typename Rule_Operator<J, std::tuple<Rule_Wrapper<T>, Ts...>, std::tuple<Rule_Wrapper<U>, Us...>>::result_type join_type;
	static join_type op(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	{
		return Rule_Operator<J, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>::op(_t, _u);
	}
};

template<Rule_Types M, Rule_Types T, typename... Ts>
struct Bound_Tuple<M, std::tuple<Rule_Wrapper<T>, Ts...>>
{
	typedef std::tuple<Rule_Wrapper<M>, Rule_Wrapper<T>, Ts...> join_type;
	static join_type op(const std::tuple<Rule_Wrapper<T>, Ts...>& _t)
	{
		return std::tuple_cat(std::make_tuple(Rule_Wrapper<M>()), _t);
	}
};

template<Rule_Types T, typename... Ts>
struct Bound_Tuple<Rule_Types::NEGATION, std::tuple<Rule_Wrapper<Rule_Types::OPTIONAL>, Rule_Wrapper<T>, Ts...>>
{
	typedef std::tuple<Rule_Wrapper<Rule_Types::FAILURE>> join_type;
	template<typename U>
	static join_type op(const U& _u)
	{
		return {};
	}
};

template<Rule_Types T, typename... Ts>
struct Bound_Tuple<Rule_Types::NEGATION, std::tuple<Rule_Wrapper<Rule_Types::NEGATION>, Rule_Wrapper<T>, Ts...>>
{
	typedef std::tuple<Rule_Wrapper<T>, Ts...> join_type;
	static join_type op(const std::tuple<Rule_Wrapper<Rule_Types::NEGATION>, Rule_Wrapper<T>, Ts...>& _t)
	{
		return tail(_t);
	}
};

template<Rule_Types T, typename... Ts>
struct Bound_Tuple<Rule_Types::OPTIONAL, std::tuple<Rule_Wrapper<Rule_Types::OPTIONAL>, Rule_Wrapper<T>, Ts...>>
{
	typedef std::tuple<Rule_Wrapper<T>, Ts...> join_type;
	static join_type op(const std::tuple<Rule_Wrapper<Rule_Types::OPTIONAL>, Rule_Wrapper<T>, Ts...>& _t)
	{
		return tail(_t);
	}
};

template<Rule_Types T, typename... Ts>
struct Bound_Tuple<Rule_Types::OPTIONAL, std::tuple<Rule_Wrapper<Rule_Types::NEGATION>, Rule_Wrapper<T>, Ts...>>
{
	typedef std::tuple<Rule_Wrapper<Rule_Types::SUCCESS>> join_type;
	static join_type op(const std::tuple<Rule_Wrapper<Rule_Types::NEGATION>, Rule_Wrapper<T>, Ts...>& _t)
	{
		return {};
	}
};

template<Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
auto operator|(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> typename Bound_Tuple<Rule_Types::DISJUNCT,
				typename std::decay<decltype(_t)>::type,
				typename std::decay<decltype(_u)>::type>::join_type
{
	return Bound_Tuple<Rule_Types::DISJUNCT,
				typename std::decay<decltype(_t)>::type,
				typename std::decay<decltype(_u)>::type>::op(_t, _u);
}

template<Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
auto operator||(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<int N, Rule_Types T, typename... Ts>
auto operator|(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TRef<N>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<int N, Rule_Types U, typename... Us>
auto operator|(const TRef<N>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<int N, Rule_Types T, typename... Ts>
auto operator||(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TRef<N>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<int N, Rule_Types U, typename... Us>
auto operator||(const TRef<N>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator|(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TError<E>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator|(const TError<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator||(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TError<E>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator||(const TError<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator|(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TWarn<E>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator|(const TWarn<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::DISJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::DISJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator||(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TWarn<E>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator||(const TWarn<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t | _u)
{
	return _t | _u;
}

template<Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
auto operator&(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> typename Bound_Tuple<Rule_Types::CONJUNCT,
				typename std::decay<decltype(_t)>::type,
				typename std::decay<decltype(_u)>::type>::join_type
{
	return Bound_Tuple<Rule_Types::CONJUNCT,
				typename std::decay<decltype(_t)>::type,
				typename std::decay<decltype(_u)>::type>::op(_t, _u);
}

template<Rule_Types T, Rule_Types U, typename... Ts, typename... Us>
auto operator&&(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<int N, Rule_Types T, typename... Ts>
auto operator&(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TRef<N>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<int N, Rule_Types T, typename... Ts>
auto operator&(const TRef<N>& _t, const std::tuple<Rule_Wrapper<T>, Ts...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<int N, Rule_Types U, typename... Us>
auto operator&&(const std::tuple<Rule_Wrapper<U>, Us...>& _t, const TRef<N>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<int N, Rule_Types U, typename... Us>
auto operator&&(const TRef<N>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator&(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TError<E>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator&(const TError<E>& _t, const std::tuple<Rule_Wrapper<T>, Ts...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator&&(const std::tuple<Rule_Wrapper<U>, Us...>& _t, const TError<E>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator&&(const TError<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator&(const std::tuple<Rule_Wrapper<T>, Ts...>& _t, const TWarn<E>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types T, typename... Ts>
auto operator&(const TWarn<E>& _t, const std::tuple<Rule_Wrapper<T>, Ts...>& _u)
	-> std::tuple<Rule_Wrapper<Rule_Types::CONJUNCT>, typename std::decay<decltype(_t)>::type, typename std::decay<decltype(_u)>::type>
{
	return std::tuple_cat(std::make_tuple(Rule_Wrapper<Rule_Types::CONJUNCT>()), std::make_tuple(_t), std::make_tuple(_u));
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator&&(const std::tuple<Rule_Wrapper<U>, Us...>& _t, const TWarn<E>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<Parse_Exceptions E, Rule_Types U, typename... Us>
auto operator&&(const TWarn<E>& _t, const std::tuple<Rule_Wrapper<U>, Us...>& _u)
	-> decltype(_t & _u)
{
	return _t & _u;
}

template<typename... Ts, typename... Us>
std::tuple<Rule_Types, Ts..., Us...> operator/(const std::tuple<Rule_Types, Ts...>& _t, const std::tuple<Rule_Types, Us...>& _u)
{
	return std::tuple_cat(std::make_tuple(Rule_Types::CONJUNCT), tail(_t), tail(_u));
}

template<Rule_Types R, typename... Ts>
auto operator-(const std::tuple<Rule_Wrapper<R>, Ts...>& _t)
	-> typename Bound_Tuple<Rule_Types::OPTIONAL, typename std::decay<decltype(_t)>::type>::join_type
{
	return Bound_Tuple<Rule_Types::OPTIONAL, typename std::decay<decltype(_t)>::type>::op(_t);
}

template<Rule_Types R, typename... Ts>
auto operator~(const std::tuple<Rule_Wrapper<R>, Ts...>& _t)
	-> typename Bound_Tuple<Rule_Types::NEGATION, typename std::decay<decltype(_t)>::type>::join_type
{
	return Bound_Tuple<Rule_Types::NEGATION, typename std::decay<decltype(_t)>::type>::op(_t);
}

bool finalized_rules = false;	// Prevent new rules from being added incidentally in case parser references a non-existant rule
std::unordered_map<std::string, Rule> rules;

decltype(rules)::mapped_type& operator"" _def( const char* _def, std::size_t )
{
	if( !rules[_def] )
	{
		std::clog << "Creating parser rule: " << _def << std::endl;
		if( finalized_rules )
		{
			throw Parse_Exceptions::PARSE_RULE_NO_DEF;
		}

		std::string def{_def};
		rules[def] = [def](mmidx) -> token_type
		{
			std::clog << "Trying parse rule: " << def << std::endl;
			return token_type{0, 0, 0, 0, 0, 0};
		};
	}

	return rules[_def];
}

std::tuple<Rule_Wrapper<Rule_Types::CHARSET>, std::string> operator"" _cset(const char* _cset, std::size_t)
{
	return std::make_tuple(Rule_Wrapper<Rule_Types::CHARSET>(), std::string{_cset});
}

std::tuple<Rule_Wrapper<Rule_Types::KEYWORD>, std::string> operator"" _keyw(const char* _keyw, std::size_t)
{
	return std::make_tuple(Rule_Wrapper<Rule_Types::KEYWORD>(), std::string{_keyw});
}

#include <algorithm>
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <memory>
//#include <boost/regex.hpp>
//#include <boost/interprocess/file_mapping.hpp>
//#include <boost/interprocess/mapped_region.hpp>

int main()
{
	try
	{
		"first"_def = "second"_def;
		"second"_def(0);
		"first"_def(0);
		auto fourth = "fourth"_def;
		finalized_rules = true;
		fourth(0);
		"third"_def(0);
	}
	catch(Parse_Exceptions _e)
	{
		std::cerr << "Unrecoverable parse error: " << _e << std::endl;
	}
	std::clog << "T<...> convertible to T<> " << std::boolalpha << std::is_convertible<std::tuple<int>, std::tuple<>>::value << std::endl;
	std::clog << "T<...> derived from T<> " << std::is_base_of<std::tuple<>, std::tuple<int>>::value << std::endl;
	std::clog << "T<...> is tuple " << Is_Tuple<std::tuple<int>>::value << std::endl;

	auto tail_test = tail(std::make_tuple(3.14, 2.71, 0, 'a',  std::string{"I am the very model of a modern major general"}, "second"_def));
	std::clog << "tail test: " << tail_test << std::endl;

	std::clog << "Tail<3> test: " << tail<3>(std::make_tuple(3.14, 2.71, 0, 'a', std::make_tuple(TRef<4>(), TWarn<Parse_Exceptions::PARSE_RULE_NO_DEF>(), TError<Parse_Exceptions::PARSE_RULE_NO_DEF>()), std::string{"I am the very model of a modern major general"}, "second"_def)) << std::endl;

// 	std::clog << "Tail<8> test: " << tail<8>(std::make_tuple(3.14, 2.71, 0, 'a',  std::string{"I am the very model of a modern major general"}, "second"_def)) << std::endl;

	std::clog << "Tail of <1> test: " << tail(std::make_tuple(std::string{"asdf"})) << std::endl;

	std::clog << "Tail of <2> test: " << tail(std::make_tuple(1, std::string{"asdf"})) << std::endl;

	std::clog << "Tail of <3> test: " << tail(std::make_tuple(1, std::string{"asdf"}, 'z')) << std::endl;

	std::clog << "Head<3> test: " << head<3>(std::make_tuple(3.14, 2.71, 0, 'a',  std::string{"I am the very model of a modern major general"}, "second"_def)) << std::endl;

// 	std::clog << "Head<8> test: " << head<8>(std::make_tuple(3.14, 2.71, 0, 'a',  std::string{"I am the very model of a modern major general"}, TError<Parse_Exceptions::PARSE_RULE_NO_DEF>(), "second"_def)) << std::endl;

// 	std::clog << "Head<4> of <1> test: " << head<4>(std::make_tuple(std::string{"asdf"})) << std::endl;

	std::clog << "Max tuple: " << tmax(std::make_tuple(1, 2, 3), std::make_tuple(1, 2, 3, 4, 5, 6)) << std::endl;
	std::clog << "Min tuple: " << tmin(std::make_tuple(1, 2, 3), std::make_tuple(1, 2, 3, 4, 5, 6)) << std::endl;
// 	std::clog << "Min tuple: " << tmin(Rule(), std::make_tuple(1, 2, 3, 4, 5, 6)) << std::endl;

	std::clog << "Max size tuple: " << tsmax(std::make_tuple((uint64_t) 1, (uint64_t) 2, (uint64_t) 3), std::make_tuple(1, 2, 3, 4, 5)) << std::endl;
	std::clog << "Min size tuple: " << tsmin(std::make_tuple((uint64_t) 1, (uint64_t) 2, (uint64_t) 3), std::make_tuple(1, 2, 3, 4, 5)) << std::endl;

	auto t = std::make_tuple(3.14, 2.71, 0, 'a', std::make_tuple("Hydrogen"_s, "Helium"_s, "Lithium"_s, "Berylium"_s, std::make_tuple("H"_s, "He"_s, "Li"_s, "Be"_s)), std::string{"I am the very model of a modern major general"}, std::make_tuple("Boron"_s, "Carbon"_s, std::make_tuple(std::make_tuple(1, 1, 2, 3, 5, 8), 'B', 'C', 'N', 'O'), "Nitrogen"_s, "Oxygen"_s), "second"_def);
	std::clog << "TMap test: " << t << "" << std::endl;

	std::clog << "Bound tuple test: " << ("ABCDEFG"_cset && ("HIJKLMN"_cset && "1234567"_cset) | "abcdefg"_cset | "hijklmn"_cset & "opqrstu"_cset & "vwxyz"_cset) << std::endl;
	std::clog << "Bound tuple test2: " << ~("ABCDEFG"_cset && "HIJKLMN"_cset && ~"1234567"_cset & TError<Parse_Exceptions::PARSE_RULE_NO_DEF>() & TWarn<Parse_Exceptions::PARSE_RULE_NO_DEF>() & TRef<2>() & ~~"abcdefg"_cset && "hijklmn"_cset && -"opqrstu"_cset & -(-"vwxyz"_cset)) << std::endl;
	std::clog << (~"template"_keyw | -("qwerty"_keyw & "asdf"_cset) && TRef<2>() && ""_keyw) << std::endl;

	return 0;
}
