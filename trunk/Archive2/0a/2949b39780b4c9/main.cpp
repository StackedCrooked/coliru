#include <cstdlib>
#include <vector>
#include <iostream>
#include <type_traits>

template <typename T> struct rng
{
    rng(T begin, T end)
		: _begin(std::move(begin))
		, _end(std::move(end))
	{
	}

	T begin() { return _begin; }
	T end() { return _end; }

	T _begin;
	T _end;
};

template <typename T> rng<T> make_rng(T begin, T end) { return{ begin, end }; }

template <typename T> struct itr
{
	itr(T&& o)
		: obj(std::move(o))
	{
	}

	bool operator!=(const itr& other) const { return obj != other.obj; }
	T operator*() const { return obj; }

	const itr& operator++()
	{
		++obj;
		return *this;
	}

	T obj;
};

template <typename T> struct val
{
	T obj;
	val(T&& value)
		: obj(std::move(value))
	{
	}

	auto begin() -> itr<decltype(std::begin(obj))> { return std::begin(obj); }
	auto end() -> itr<decltype(std::end(obj))> { return std::end(obj); }
};

template <typename T> struct ref
{
	T& obj;
	ref(T& value)
		: obj(value)
	{
	}

	auto begin() -> itr<decltype(std::begin(obj))> { return std::begin(obj); }
	auto end() -> itr<decltype(std::end(obj))> { return std::end(obj); }
};

template <typename T>
auto make_itr(T&& t) ->
typename std::conditional<std::is_lvalue_reference<decltype(t)>::value, ref<T>, val<T>>::type
{
	return std::forward<T>(t);
}

template <typename T>
auto make_itr(T begin, T end) -> decltype(make_itr(make_rng(std::move(begin), std::move(end))))
{
	return make_itr(make_rng(std::move(begin), std::move(end)));
}

int main()
{
	for (auto t : make_itr(std::vector<int>{ 1, 2, 3, 4 }))
	{
		std::cout << *t << std::endl;
	}

	std::vector<int> v{ 1, 2, 3, 4 };
	for (auto t : make_itr(v))
	{
		std::cout << *t << std::endl;
	}

	for (auto t : make_rng(v.begin(), v.end()))
	{
		std::cout << t << std::endl;
	}

	for (auto t : make_itr(make_rng(v.begin(), v.end())))
	{
		std::cout << *t << std::endl;
	}

	for (auto t : make_itr(v.begin(), v.end()))
	{
		std::cout << *t << std::endl;
	}

	for (auto t = v.begin(); t != v.end(); ++t)
	{
		std::cout << *t << std::endl;
	}

	return EXIT_SUCCESS;
}