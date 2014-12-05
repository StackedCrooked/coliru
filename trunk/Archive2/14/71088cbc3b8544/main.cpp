#include <vector>
#include <iostream>

// How can I either make this SFINAE struct do the right thing for free
// functions or use overloading to solve the problem?

template<typename F, typename T>
struct takes_2_args
{
    typedef char true_type[1];
	typedef char false_type[2];

	// I don't know what to do here, I want to tell the compiler,
	// "accept any callable type that returns a U and takes
	// either (const U) or (const U, const std::vector<U>&)"

	// Let's try for just function objects first
	template<typename G, typename U>
	static true_type& test(U (G::*)(const U, const std::vector<U>&));

	// maybe this for free functions?
	// template<typename, typename U>
	// static true_type& test(U (&)(const U, const std::vector<U>&));

	template<typename, typename>
	static false_type& test(...);

	// Compile error here, obviously ::operator() is no good for a free function
	static const bool value =
		(sizeof(test<F, T>(&F::operator())) == sizeof(true_type));
};


// overloads for functors
// These use SFINAE to check if functor takes 2 arguments
// Right now free functions end up here and the compiler complains inside the
// SFINAE struct... :(

template<typename F, typename T>
std::vector<T> map_vec(
	const F& fnc,
	const std::vector<T>& source)
{
	// silence errors
	(void)fnc;
	(void)source;

	// The compiler should optimize out this if/else once instantiated but it
	// would be nice to know how to do this with templates.
	if (takes_2_args<F, T>::value)
	{
		std::cout << "takes 2nd arg!" << std::endl;
		// do mapping loop with func
		return std::vector<T>();
	}
	else
	{
		std::cout << "does not take 2nd arg!" << std::endl;
		// do mapping loop with func
		return std::vector<T>();
	}
}


// overloads for free functions
// Maybe I can somehow avoid the SFINAE struct with these overloads?

template<typename T>
std::vector<T> map_vec(
	const T (fnc)(const T),
	const std::vector<T>& source)
{
	// silence errors
	(void)fnc;
	(void)source;

	std::cout << "does not take 2nd arg!" << std::endl;
}

template<typename T>
std::vector<T> map_vec(
	const T (fnc)(const T, const std::vector<T>&),
	const std::vector<T>& source)
{
	// silence errors
	(void)fnc;
	(void)source;

	std::cout << "does not take 2nd arg!" << std::endl;
	return std::vector<T>();
}


// free functions

int foo(const int x) {
	// std::cout << "foo(" << x << ")" << std::endl;
	return x * 2;
}

int bar(const int x, const std::vector<int>& v) {
	return x * 2 + v.size();
}


// functors

class AddNum
{
public:
	AddNum(const int num) : num_(num) {}

	int operator()(const int x) const
	{ return x + num_; }

private:
	const int num_;
};

class AddNumMulSize
{
public:
	AddNumMulSize(const int num) : num_(num) {}

	int operator()(const int x, const std::vector<int>& v)
	{ return (x + num_) * v.size(); }

private:
	const int num_;
};


// test program

int main()
{
	std::vector<int> v;
	// wow, so easy to forget such barbarity was the norm 3 years ago...
	v.reserve(3);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	// fails to compile
	// const std::vector<int> a = map_vec(foo, v);
	// const std::vector<int> b = map_vec(bar, v);

	// these do the right thing
	const AddNum add2(2);
	const std::vector<int> c = map_vec(add2, v);

	const AddNumMulSize add2mulsz(2);
	const std::vector<int> d = map_vec(add2mulsz, v);
}
