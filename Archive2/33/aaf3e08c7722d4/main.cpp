#define BOOST_MPL_LIMIT_MAP_SIZE 50
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/typeof/std/utility.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/set.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/partition.hpp>
#include <boost/mpl/for_each.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <typeinfo>

using namespace boost;

struct to_string_helper {
private:
    std::ostream& out;

public:
	to_string_helper(std::ostream& out) : out(out) {}

	template<typename T, typename U>
	void operator()(mpl::pair<T, U>) {
		out << typeid(T).name() << " -> " << typeid(U).name() << std::endl;
	}
};

template<typename Map>
void to_string(std::ostream& out) {
	mpl::for_each<Map>(to_string_helper(out));
}

struct Empty {
    using type = void;
};

template<typename T>
struct Left {
	using type = T;
};

template<typename... Ts>
struct Right {
	using type = mpl::list<Ts...>;
};

template<int N>
struct Terminal {
	using type = std::string;
};

template<typename T, typename U>
struct IsValidFormalParam {
	static const bool value =
	std::is_same<T, U>::value;
};

template<int N>
struct IsValidFormalParam<Terminal<N>, std::string> {
	static const bool value = true;
};

template<typename Vector1, typename Vector2, int i>
struct VerifyRightHandSideHelper {
	using type = std::integral_constant<
		bool,
		IsValidFormalParam<
			typename mpl::at_c<Vector1, i>::type,
			typename mpl::at_c<Vector2, i + 1>::type
		>::value
		&& VerifyRightHandSideHelper<Vector1, Vector2, i - 1>::type::value
	>;
};

template<typename Vector1, typename Vector2>
struct VerifyRightHandSideHelper<Vector1, Vector2, -1> {
	using type = std::true_type;
};

template<typename Vector1, int N, typename Vector2, int M>
struct VerifyRightHandSide {
	//First verify equal length
	static const bool value = mpl::if_c<
		N == M,
		typename VerifyRightHandSideHelper<Vector1, Vector2, N-1>::type,
		std::false_type
	>::type::value;
};

template<int N, typename Vector, int M>
struct VerifyRightHandSide<mpl::list<Empty>, N, Vector, M> {
	//Specialize for deriving the empty string. We expect no parameters
	static const bool value = (M == 0);
};

template<typename Left, typename Right, typename Action>
struct Production {
	using left = Left;
	using right = Right;
	//Verify the production returns the correct type
	using result_type = typename function_types::result_type<BOOST_TYPEOF(&Action::operator())>::type;
	static_assert(std::is_same<typename Left::type, result_type>::value,
		"Result type of action must match the left hand side of the production.");

	//Verify formal param types match the right hand side
	using arg_types = typename function_types::parameter_types<BOOST_TYPEOF(&Action::operator())>::type;
	static_assert(
		VerifyRightHandSide<
			typename Right::type,
			mpl::size<typename Right::type>::value,
			arg_types,
			mpl::size<arg_types>::value-1 //We subtract one to remove the this-ptr
		>::value,
		"Invalid formal parameters for action"
	);
};

//Union two sets of type boost::mpl::set
template<typename Set1_, typename Set2_>
struct union_ {
	using Set1 = typename mpl::if_<
		std::is_same<typename Set1_::type, mpl::void_>,
		mpl::set<>,
		Set1_
	>::type;

	using Set2 = typename mpl::if_<
		std::is_same<typename Set2_::type, mpl::void_>,
		mpl::set<>,
		Set2_
	>::type;

	using type = typename mpl::fold<
		Set1,
		Set2,
		mpl::insert<mpl::_1, mpl::_2>
	>::type;
};

template<typename P, typename... Ps>
struct LrParserHelper : LrParserHelper<Ps...> {
private:
	//Ensure that the production is instantiated
	//so that static_asserts are evaluated
	P p;
};

template<
	typename First__,
	typename Follow__,
	typename Nullable__,
	typename P_, typename... Ps_>
struct FirstFollowNullable {
private:
	//Check if each production in Ys is nullable
	template<typename Nullable, typename Ys>
	struct isNullable {
		static const bool value =
			mpl::fold<
				Ys,
				std::true_type,
				mpl::if_<
					mpl::has_key<Nullable, mpl::_2>,
					mpl::_1,
					std::false_type
				>
			>::type::value;
	};

	using k = typename mpl::int_<
		mpl::size<typename P_::right::type>::value
	>;

	template<typename i, typename j,
		typename First_, typename Follow_, typename Nullable_,
		typename P, typename... Ps>
	struct Loop {
	private:
		using X = typename P::left::type;
		//Y1, ..., YN
		using Ys = typename P::right::type;
		using Yi = typename mpl::at<Ys, i>::type;
		using Yj = typename mpl::at<Ys, j>::type;

		//Y1, ..., Yi-1
		using Ys2 = typename mpl::erase<
			Ys,
			typename mpl::advance<
				typename mpl::begin<Ys>::type,
				i
			>::type
		>::type;

		//Yi+1, ..., Yk
		using Ys3 = typename mpl::erase<
			Ys,
			typename mpl::begin<Ys>::type,
			typename mpl::advance<
				typename mpl::begin<Ys>::type,
				i
			>::type
		>::type;
		//Yi+1, ..., Yj-1
		using Ys4 = typename mpl::erase<
			Ys3,
			typename mpl::advance_c<
				typename mpl::begin<Ys3>::type,
				i::value - j::value
			>::type
		>::type;

		using Nullable2 = typename mpl::if_<
			isNullable<Nullable_, Ys>,
			typename mpl::insert<Nullable_, X>::type,
			Nullable_
		>::type;

		using First2 = typename mpl::eval_if<
			isNullable<Nullable2, Ys2>,
			mpl::insert<
				typename mpl::erase_key<First_, X>::type,
				mpl::pair<
					X,
					typename union_<
						mpl::at<First_, X>,
						mpl::at<First_, Yi>
					>::type
				>
			>,
			mpl::identity<First_>
		>::type;

		using Follow2 = typename mpl::eval_if<
			isNullable<Nullable2, Ys3>,
			mpl::insert<
				typename mpl::erase_key<Follow_, Yi>::type,
				mpl::pair<
					Yi,
					typename union_<
						mpl::at<Follow_, Yi>,
						mpl::at<Follow_, X>
					>::type
				>
			>,
			mpl::identity<Follow_>
		>::type;

		using Follow3 = typename mpl::eval_if<
			isNullable<Nullable2, Ys4>,
			mpl::insert<
				typename mpl::erase_key<Follow2, Yi>::type,
				mpl::pair<
					Yi,
					typename union_<
						mpl::at<Follow2, Yi>,
						mpl::at<First2, Yj>
					>::type
				>
			>,
			mpl::identity<Follow2>
		>::type;
		
		using T = Loop<
			i,
			typename j::next,
			First2,
			Follow3,
			Nullable2,
			P,
			Ps...
		>;

	public:
		using First = typename T::First;
		using Follow = typename T::Follow;
		using Nullable = typename T::Nullable;
	};

	template<typename i,
		typename First_, typename Follow_, typename Nullable_,
		typename P, typename... Ps>
	struct Loop<i, k, First_, Follow_, Nullable_, P, Ps...> {
	private:
		using T = Loop<
			typename i::next,
			mpl::int_<0>,
			First_,
			Follow_,
			Nullable_,
			P, Ps...
		>;
	public:
		using First = typename T::First;
		using Follow = typename T::Follow;
		using Nullable = typename T::Nullable;
	};

	template<typename First_, typename Follow_, typename Nullable_, typename P, typename P2, typename... Ps>
	struct Loop<k, mpl::int_<0>, First_, Follow_, Nullable_, P, P2, Ps...> {
	private:
		using T = Loop<mpl::int_<0>, mpl::int_<0>, First_, Follow_, Nullable_, P2, Ps...>;
	public:
		using First = typename T::First;
		using Follow = typename T::Follow;
		using Nullable = typename T::Nullable;
	};

	template<typename First_, typename Follow_, typename Nullable_, typename P>
	struct Loop<k, mpl::int_<0>, First_, Follow_, Nullable_, P> {
		using First = First_;
		using Follow = Follow_;
		using Nullable = Nullable_;
	};

	template<typename isDone, int N, typename First_, typename Follow_, typename Nullable_, typename... Ps>
	struct Repeat {
	private:
		using T = Loop<
			mpl::int_<0>,
			mpl::int_<0>,
			First_, Follow_, Nullable_,
			Ps...
		>;

		/*
			typename mpl::and_<
				typename std::is_same<
					First_, typename T::First
				>::type,
				typename std::is_same<
					Follow_, typename T::Follow
				>::type,
				typename std::is_same<
					Nullable_, typename T::Nullable
				>::type
			>::type
		*/

		using U = Repeat<
			mpl::bool_<N == 2>,
			N+1,
			typename T::First,
			typename T::Follow,
			typename T::Nullable,
			Ps...
		>;
	public:
		using First = typename U::First;
		using Follow = typename U::Follow;
		using Nullable = typename U::Nullable;
	};

	template<typename First_, int N, typename Follow_, typename Nullable_, typename... Ps>
	struct Repeat<mpl::true_, N, First_, Follow_, Nullable_, Ps...> {
		using First = First_;
		using Follow = Follow_;
		using Nullable = Nullable_;
	};

	using Nullable2 = typename mpl::if_<
		isNullable<Nullable__, typename P_::right::type>,
		typename mpl::insert<Nullable__, typename P_::left::type>::type,
		Nullable__
	>::type;

	using T = Repeat<mpl::false_, 0, First__, Follow__, Nullable2, P_, Ps_...>;

public:
	using First = typename T::First;
	using Follow = typename T::Follow;
	using Nullable = typename T::Nullable;
};

template<typename... Ps_>
struct LrParser : LrParserHelper<Ps_...> {
private:

	template<typename P, typename... Ps>
	struct ConsFollow {
		using type = typename mpl::insert<
			typename ConsFollow<Ps...>::type,
			mpl::pair<
				typename P::left::type,
				mpl::set<>
			>
		>::type;
	};

	template<typename P>
	struct ConsFollow<P> {
		using type = mpl::map<
			mpl::pair<
				typename P::left::type,
				mpl::set<>
			>
		>;
	};

	template<typename Map, typename T>
	struct AddSingleTerminal {
		using type = Map;
	};

	template<typename Map, int N>
	struct AddSingleTerminal<Map, Terminal<N>> {
		using type = typename mpl::if_<
			mpl::has_key<Map, Terminal<N>>,
			Map,
			typename mpl::insert<
				Map,
				mpl::pair<
					Terminal<N>,
					mpl::set<Terminal<N>>
				>
			>::type
		>::type;
	};

	template<typename Map, typename Rhs>
	struct AddTerminals {
	public:
		using type = typename mpl::fold<
			Rhs,
			Map,
			AddSingleTerminal<mpl::_1, mpl::_2>
		>::type;
	};

	template<typename P, typename... Ps>
	struct ConsFirst {
		using type = typename AddTerminals<
			typename ConsFirst<Ps...>::type,
			typename P::right::type
		>::type;
	};

	template<typename P>
	struct ConsFirst<P> {
		using type = typename AddTerminals<
			mpl::map<>,
			typename P::right::type
		>::type;
	};

	using ffn = FirstFollowNullable<
		typename ConsFirst<Ps_...>::type,
		typename ConsFollow<Ps_...>::type,
		mpl::set<>,
		Ps_...>;
	using First = typename ffn::First;
	using Follow = typename ffn::Follow;
	using Nullable = typename ffn::Nullable;
	
public:
	LrParser() {
		std::ofstream outfile("out.txt");
		to_string<First>(std::cout);
		outfile.close();
	}

};

template<typename P>
struct LrParserHelper<P> {
private:
	P p;
};

struct X {
	using type = X;

	std::string s;
	X(std::string s) : s(move(s)) {}
};

struct Y {
	using type = Y;

	std::string s;
	Y(std::string s) : s(move(s)) {}
};

struct Z {
	using type = Z;

	std::string s;
	Z(std::string s) : s(move(s)) {}
};

struct Rule1 {
	Z operator()(std::string) {
		return Z("");
	}
};

struct Rule2 {
	Z operator()(X, Y, Z) {
		return Z("");
	}
};

struct Rule3 {
	Y operator()() {
		return Y("");
	}
};

struct Rule4 {
	Y operator()(std::string) {
		return Y("");
	}
};

struct Rule5 {
	X operator()(Y) {
		return X("");
	}
};

struct Rule6 {
	X operator()(std::string) {
		return X("");
	}
};

int main(int argc, char* argv []) {
	using d = Terminal<0>;
	using c = Terminal<1>;
	using a = Terminal<2>;

	LrParser<
		Production<
			Left<Z>,
			Right<d>,
			Rule1
		>,
		Production<
			Left<Z>,
			Right<X, Y, Z>,
			Rule2
		>,
		Production<
			Left<Y>,
			Right<Empty>,
			Rule3
		>,
		Production<
			Left<Y>,
			Right<c>,
			Rule4
		>,
		Production<
			Left<X>,
			Right<Y>,
			Rule5
		>,
		Production<
			Left<X>,
			Right<a>,
			Rule6
		>
	>();
	return 0;
}