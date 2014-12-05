#include <vector>
#include <iostream>

template<typename F, typename T>
struct takes_2nd_arg
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
	template<typename, typename U>
	static true_type& test(U (&)(const U, const std::vector<U>&));

	template<typename, typename>
	static false_type& test(...);

	// Huh, what happens here to accept either a function or functor?
	static const bool value =
		(sizeof(test<F, T>(&F::operator())) == sizeof(true_type));
};

template<typename F, typename T>
std::vector<T> map_vec(
	const F& fnc,
	const std::vector<T>& source)
{
	// silence errors
	(void)fnc;
	(void)source;

	if (takes_2nd_arg<F, T>::value)
	{
		std::cout << "takes 2nd arg!" << std::endl;
		return std::vector<T>();
	}
	else
	{
		std::cout << "takes 2nd arg!" << std::endl;
		return std::vector<T>();
	}
}

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

int main()
{
	std::vector<int> v;
	// wow, so easy to forget such barbarity was the norm 3 years ago...
	v.reserve(3);
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);

	const AddNum add2(2);
	const std::vector<int> c = map_vec(add2, v);

	const AddNumMulSize add2mulsz(2);
	const std::vector<int> d = map_vec(add2mulsz, v);
}