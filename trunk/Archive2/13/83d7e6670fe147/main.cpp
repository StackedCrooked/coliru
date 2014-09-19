#include <functional>
#include <memory>

template <class... Signatures>
class DelegateFactory
{
    // tuple storing our delegates
	typedef std::tuple<std::function<Signatures>...> tuple_type;
	tuple_type m_delegates;

	// helper template to check if N indexes the delegate for type T
	template<size_t N, class T> 
	using is_index_of_type = std::is_same<T*, typename std::tuple_element<N, tuple_type>::type::result_type>;

	// helper template go get the delegate index for type T
	template<class T>
	struct index_of_type
	{
		template <size_t N, bool IsIndex>
		struct impl
		{
			// not the correct index, try the next one
			static const size_t value = impl<N + 1, is_index_of_type<N + 1, T>::value>::value;
		};

		template <size_t N>
		struct impl < N, true >
		{
			// this is the correct index
			static const size_t value = N;
		};

		static const size_t value = impl<0, is_index_of_type<0, T>::value>::value;
	};

public:
	template <class T, class F>
	void register_delegate(F functor)
	{
		// put it into the tuple
		std::get<index_of_type<T>::value>(m_delegates) = functor;
	}

	template <class T, class... Args>
	std::unique_ptr<T> create(Args... args)
	{
		// call the delegate with the given arguments and put the pointer into a unique_ptr
		return std::unique_ptr<T>{ std::get<index_of_type<T>::value>(m_delegates)(std::forward<Args>(args)...) };
	}
};

struct A
{
	A(int, float)
	{
	}
};

struct B
{
	B()
	{
	}
};

int main()
{
	DelegateFactory
	<
		A*(int, float), // this factory can construct a A from parameters int and float...
		B*() // and a B without parameters
	> factory;

	// register delegate for type A
	factory.register_delegate<A>([](int i, float f)
	{
		return new A{ i, f };
	});

	// register delegate for type B
	factory.register_delegate<B>([]
	{
		return new B;
	});

	auto a = factory.create<A>(42, 21.f);
	auto b = factory.create<B>();
}