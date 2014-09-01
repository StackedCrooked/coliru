#include <iostream>
#include <vector>

#include <boost/optional.hpp>


// functor keeping a value that it adds to every given container
template <typename T>
struct conj_functor
{
    conj_functor(T value)
		: m_value{ value }
	{
	}

	template <typename U>
	U operator()(U collection) const
	{
		// use insert to be compatible with all STL containers
		collection.insert(collection.end(), m_value);
		return collection;
	}

	T m_value;
};

// helper function that creates a conj_functor with type deduction
template <typename T>
conj_functor<T> conj(T value)
{
	return{ value };
}

// functor to indexed access into containers
struct get
{
	explicit get(size_t idx)
		: m_idx{ idx }
	{
	}

	template <typename U>
	boost::optional<typename U::value_type> operator()(const U& collection) const
	{
		// use iterators for maximum compatibility
		auto itr = collection.begin();

		// check if we are out of bounds
		if (long(m_idx) >= std::distance(itr, collection.end()))
			return boost::none;

		// return the value
		std::advance(itr, m_idx);
		return *itr;
	}

	size_t m_idx;
};

// functor for incrementing values
struct inc_function
{
	// we need some kind of type switch, because we want to handle both T and boost::optional<T>
	template <typename T>
	struct inc_impl
	{
		static T doit(T value)
		{
			// plain value, just increment it
			return ++value;
		}
	};

	template <typename T>
	struct inc_impl < boost::optional<T> >
	{
		static boost::optional<T> doit(boost::optional<T> value)
		{
			// it's a boost::optional, assert that it holds a value and increment it
			assert(value);
			return ++(*value);
		}
	};


	template <typename T>
	T operator()(T value) const
	{
		return inc_impl<T>::doit(value);
	}
};

// global constant inc functor
const inc_function inc;


/* C++14 version
template <typename Value>
decltype(auto) forward(Value v) {
    return v;
}

template <typename Value, typename Func, typename... Funcs>
decltype(auto) forward(Value v, Func f, Funcs... fs) {
    return forward(f(v), fs...);
}
*/

template <typename Value>
Value forward(Value v) {
    return v;
}

template <typename Value, typename Func, typename... Funcs>
auto forward(Value v, Func f, Funcs... fs) -> decltype(forward(f(v), fs...)) {
    return forward(f(v), fs...);
}


int main()
{
	std::vector<double> my_vec;

	boost::optional<double> result = forward(my_vec, conj(0.1), get(0), inc);

	std::cout << *result << std::endl;
}