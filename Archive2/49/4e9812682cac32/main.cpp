
/*
The serialization library I'm writing has a uniform interface between
types of "serializers", which read or write objects. The serialization
implementation for objects is supplied through a pair of read() and
write() functions, or a single generic serialize() function.

Serialization functions can be defined as member functions or as free
functions (e.g., for builtins and classes that have already been
defined or cannot be modified).

Currently the traits simply test if a serialization function is
callable by using decltype and declval -- e.g., free function
serialize():
*/

template<class T, class Ser>
static auto
has_non_member_serialize_impl(signed) ->
    decltype(
		serialize(
			std::declval<Ser&>(),
			std::declval<typename std::decay<T>::type&>()
		),
		std::true_type{}
	)
;

template<class, class>
static std::false_type
has_non_member_serialize_impl(...);
template<class T, class Ser>
struct has_non_member_serialize
	: public decltype(has_non_member_serialize_impl<T, Ser>(0))
{};

/*
For write() implementations, the T is const, but for serialize() and
read(), the T is always mutable, so there's some const qualification
in the mix.

The interface of a serializer is a single operator()(...).
The parameters are passed through a few functions where the
serialization-function availability is switched upon by enable_if.

Here's what the base output serializer looks like
(somewhat simplified):
*/

template<bool const value, class T = void>
using enable = typename std::enable_if<value, T>::type;

template<class Impl>
class OutputSerializer {
private:
	using impl_type = Impl;
	using this_type = OutputSerializer<impl_type>;

	impl_type* m_impl;

protected:
	OutputSerializer(impl_type& impl)
		: m_impl(&impl)
	{}

// serialize
	template<class T>
	enable<
		has_member_serialize<T, impl_type>::value &&
		!has_non_member_serialize<T, impl_type>::value
	>
	process_impl(T const& value) {
		// For output, Ts are most likely going to be supplied
		// immutable, so we take them as immutable. But the
		// serialize() function required mutable access for input, so
		// we have to const_cast. Yes, terrible, I know. Worth it.
		const_cast<T&>(value).serialize(*m_impl);
	}

	template<class T>
	enable<
		!has_member_serialize<T, impl_type>::value &&
		has_non_member_serialize<T, impl_type>::value
	>
	process_impl(T const& value) {
		serialize(*m_impl, const_cast<T&>(value));
	}

// write
	template<class T>
	enable<
		has_member_write<T, impl_type>::value &&
		!has_non_member_write<T, impl_type>::value
	>
	process_impl(T const& value) {
		const_cast<T&>(value).write(*m_impl);
	}

	template<class T>
	enable<
		!has_member_write<T, impl_type>::value &&
		has_non_member_write<T, impl_type>::value
	>
	process_impl(T const& value) {
		write(*m_impl, value);
	}

// process
	void
	process() const noexcept {}

	template<class H>
	void
	process(H&& head) {
		// Calls process_impl on the implementation if there is one,
		// falling back to the base implementation
		m_impl->process_impl(std::forward<H>(head));
	}

	template<
		class H,
		class... R
	>
	void
	process(
		H&& head,
		R&&... rest
	) {
		process(std::forward<H>(head));
		process(std::forward<R>(rest)...);
	}

public:
	template<class... P>
	void
	operator()(P&&... args) {
		process(std::forward<P>(args)...);
	}
};

/*
That's all fine until you get to inheritance with a base-class which
implements read() & write() and where the derived class implements
only serialize(). Apart from the ambiguity (all serialization traits
are yielding true), I don't want a class to be serializable as its
base class without an explicit cast.

The traits currently implicitly cast to base-classes, which causes
the ambiguity. If I constrain the traits to only yield true for the T
(i.e., without casting), I solve the ambiguity and get the behavior I
desire.

Example (unsimplified):
*/

struct B {
	signed a;

	virtual ~B() = 0;
	B(signed a) : a(a) {}

	template<class Ser>
	inline void read(Ser& ser) {
		// const_safe simply static_casts constness based on the
		// serializer type of Ser to avoid mutation when outputting
		auto& self = const_safe<Ser>(*this);
		ser(self.a);
	}

	template<class Ser>
	inline void write(Ser& ser) const {
		auto& self = const_safe<Ser>(*this);
		ser(self.a);
	}
};

inline
B::~B() = default;

struct D : public B {
	unsigned b;

	~D() override = default;
	D(signed a, unsigned b) : B(a), b(b) {}
};

template<class Ser>
inline void serialize(Ser& ser, D& d) {
	auto& self = const_safe<Ser>(d);
	ser(
		base_cast<B>(self),
		self.b
	);
}
