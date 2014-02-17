#include <cstdint>
#include <functional>
#include <unordered_map>
#include <assert.h>

template <class RET, class ...ARG>
class fl;

template <class RET, class ...ARG>
class fl<RET(ARG...)>
{
private:
    template <class T>
	struct identity
	{
		virtual ~identity() {}

		typedef T type;
	};

	template <class T>
	struct _function_signature : _function_signature<decltype(&T::operator())>
	{};

	template <class R>
	struct _function_signature<R()> : identity<R()>
	{};

	template <class R, class... A>
	struct _function_signature<R(A...)> : identity<R(A...)>
	{};

	template <class R>
	struct _function_signature<R(*)()> : _function_signature<R()>
	{};

	template <class R, class... A>
	struct _function_signature<R(*)(A...)> : _function_signature<R(A...)>
	{};

	template <class C, class R>
	struct _function_signature<R(C::*)()> : _function_signature<R()>
	{};

	template <class C, class R, class ...A>
	struct _function_signature<R(C::*)(A...)> : _function_signature<R(A...)>
	{};

	template <class C, class R>
	struct _function_signature<R(C::*)() const> : _function_signature<R()>
	{};

	template <class C, class R, class... A>
	struct _function_signature<R(C::*)(A...) const> : _function_signature<R(A...)>
	{};

	template <class T>
	struct function_signature : _function_signature<T>
	{};

public:
	fl(void);
	~fl(void);

	fl(fl const&) = delete;
	fl& operator=(fl const&) = delete;

	fl(fl&& p_o) /*noexcept*/;
	fl& operator=(fl&& p_o) /*noexcept*/;

	template <class callable, class... arguments>
	uint64_t add(callable&& p_f, arguments&&... p_args);
	bool remove(uint64_t p_id);
	bool exists(uint64_t p_id);
	void call(ARG... p_args);
	RET call(uint64_t p_id, ARG... p_args);

private:
	std::unordered_map<uint64_t, std::function<RET(ARG...)>> m_functions;
	uint64_t m_id;

};

template <class RET, class ...ARG>
fl<RET(ARG...)>::fl(void) :
m_functions(),
m_id(0)
{}

template <class RET, class ...ARG>
fl<RET(ARG...)>::~fl(void)
{}

template <class RET, class ...ARG>
fl<RET(ARG...)>::fl(fl<RET(ARG...)>&& p_o) /*noexcept*/ :
m_functions(std::move(p_o.m_functions)),
m_id(p_o.m_id)
{}

template <class RET, class ...ARG>
fl<RET(ARG...)>& fl<RET(ARG...)>::operator=(fl<RET(ARG...)>&& p_o) /*noexcept*/
{
	m_functions = std::move(p_o.m_functions);
	m_id = p_o.m_id;

	return *this;
}

template <class RET, class ...ARG>
template <class callable, class... arguments>
uint64_t fl<RET(ARG...)>::add(callable&& p_f, arguments&&... p_args)
{

	static_assert(std::is_same<RET(ARG...), typename function_signature<callable>::type>::value, "invalid");

	m_id++;

	if (m_functions.emplace(m_id, std::move(std::function<RET(ARG...)>(std::bind(std::forward<callable>(p_f), std::forward<arguments>(p_args)...)))).second)
	{
		return m_id;
	}
	else
	{
		return 0;
	}
}

template <class RET, class ...ARG>
bool fl<RET(ARG...)>::remove(uint64_t p_id)
{
	return (bool)m_functions.erase(p_id);
}

template <class RET, class ...ARG>
bool fl<RET(ARG...)>::exists(uint64_t p_id)
{
	return (m_functions.find(p_id) == m_functions.end()) ? false : true;
}

template <class RET, class ...ARG>
void fl<RET(ARG...)>::call(ARG... p_args)
{
	for (auto const& i : m_functions)
	{
		i.second(p_args...);
	}
}

template <class RET, class ...ARG>
RET fl<RET(ARG...)>::call(uint64_t p_id, ARG... p_args)
{
	return m_functions.at(p_id)(p_args...);
}

void test(void)
{
	printf("test\n");
}

int main()
{
	fl<void(void)> f;
    uint64_t id;

	id = f.add(&test);

	f.call(id);
}
