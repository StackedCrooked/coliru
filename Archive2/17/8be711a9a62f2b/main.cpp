#include <tuple>
#include <iostream>

// this helper struct returns the index of the first matching type T within Tuple
template <class Tuple, class T>
struct find_type_index
{
	template <size_t Idx, class T1, class T2>
	struct impl
	{
        // the type T2 at Idx differs from T1, so move on
		static const auto value = impl<Idx + 1, T1, typename std::tuple_element<Idx + 1, Tuple>::type>::value;
	};

	template <size_t Idx, class T1>
	struct impl<Idx, T1, T1>
	{
        // type T2 at Idx equals T1, return this index
		static const auto value = Idx;
	};

    // use recursion to find the index
	static const auto value = impl<0, T, typename std::tuple_element<0, Tuple>::type>::value;
};

template <class ... Mixins>
class GameObject
{
    // all components are stored within the tuple
    typedef std::tuple<Mixins...> mixin_tuple;
    static const auto _numComponents = std::tuple_size<mixin_tuple>::value;
    mixin_tuple _components;
    
public:
	GameObject(Mixins&&... mixins) : _components{ std::forward<Mixins>(mixins)... } {}

	size_t getNumComponents() const { return _numComponents; };

	template <typename T>
	T* getComponent() {
		static const auto index = find_type_index<mixin_tuple, T>::value;
		return getComponent<index>();
	}

	template <size_t Index>
	auto getComponent() -> decltype(&std::get<Index>(_components)) {
		static_assert(Index < _numComponents, "getComponent: index out of range");
		return &std::get<Index>(_components);
	}

	void update() {
        // use recursion to update all components
		update_impl<0>();
	}

private:
	template <size_t Index>
	typename std::enable_if<Index != _numComponents>::type update_impl() {
		getComponent<Index>()->update();
		update_impl<Index + 1>();
	}

    template <size_t Index>
	typename std::enable_if<Index == _numComponents>::type update_impl() {}
};

// test component A
struct A 
{
    void update()
    {
		std::cout << "A::update" << std::endl;
	}
};

// test component B
struct B
{
	void update()
	{
		std::cout << "B::update" << std::endl;
	}
};

int main()
{
	GameObject<A, B> mixin(A{}, B{});
	mixin.update();
	mixin.getComponent<A>()->update();
	mixin.getComponent<1>()->update();
}