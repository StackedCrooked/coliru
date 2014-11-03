#include <type_traits>
#include <utility>
#include <new>
#include <stdexcept>
#include <cstddef>

namespace Util
{
static struct left_tag{} const left = {};
static struct right_tag{} const right = {};

template<class TLeft, class TRight>
class Either
{
    enum class State
    {
    	uninitialised,
		left, right
	};
    
public:    
    template<class T>
    Either(left_tag, T&& v)
        : m_state(State::left)
    {
        Make<TLeft>(std::forward<T>(v));
    }
    
    template<class T>
    Either(right_tag, T&& v)
        : m_state(State::right)
    {
        Make<TRight>(std::forward<T>(v));
    }
    
    Either(Either const& other)
        : m_state(other.m_state)
    {
        if (IsLeft())
            Make<TLeft>(other.Get<TLeft>());
        else if (IsRight())
            Make<TRight>(other.Get<TRight>());
    }
    
    Either(Either&& other)
        : m_state(other.m_state)
    {
        if (IsLeft())
            Make<TLeft>(std::move(other.Get<TLeft>()));
        else if (IsRight())
            Make<TRight>(std::move(other.Get<TRight>()));
    }
    
    ~Either(){ Destroy(); }
    
    Either& operator=(Either other)
    {   
        if (other.IsLeft())
            Assign(left, std::move(other.Get<TLeft>()));
        else if (other.IsRight())
            Assign(right, std::move(other.Get<TRight>()));

		return *this;
    }

	template<class T>
	Either& Assign(left_tag, T&& v)
	{
		Destroy();
		Make<TLeft>(std::forward<T>(v));
		m_state = State::left;
		return *this;
	}

	template<class T>
	Either& Assign(right_tag, T&& v)
	{
		Destroy();
		Make<TRight>(std::forward<T>(v));
		m_state = State::right;
		return *this;
	}

	bool IsLeft() const { return m_state == State::left; }
	bool IsRight() const { return m_state == State::right; }
    
    template<class FL, class FR>
    auto Merge(FL&& onLeft, FR&& onRight)
		-> decltype(onLeft(std::declval<TLeft&>()))
    {
    	typedef typename std::result_of<FL(TLeft&)>::type left_result;
        typedef typename std::result_of<FR(TRight&)>::type right_result;
        static_assert(std::is_same<left_result, right_result>::value,
            "Either<L, R>::Merge functors need to return the same type");
            
        FLASSERTF(m_state != State::uninitialised, "Either<L, R>::Merge used after destruction");
        if (IsLeft())
            return std::forward<FL>(onLeft)(Get<TLeft>());
        else if (IsRight())
            return std::forward<FR>(onRight)(Get<TRight>());
        throw std::runtime_error("Either<L, R>::Merge used after destruction");
    }
    
    template<class FL, class FR>
    auto Merge(FL&& onLeft, FR&& onRight) const
		-> decltype(onLeft(std::declval<TLeft const&>()))
    {
    	typedef typename std::result_of<FL(TLeft const&)>::type left_result;
        typedef typename std::result_of<FR(TRight const&)>::type right_result;
        static_assert(std::is_same<left_result, right_result>::value,
            "Either<L, R>::Merge functors need to return the same type");
            
        FLASSERTF(m_state != State::uninitialised, "Either<L, R>::Merge used after destruction");
        if (IsLeft())
            return std::forward<FL>(onLeft)(Get<TLeft>());
        else if (IsRight())
            return std::forward<FR>(onRight)(Get<TRight>());
        throw std::runtime_error("Either<L, R>::Merge used after destruction");
    }
    
    template<class F>
    void OnLeft(F&& f){ if (IsLeft()) std::forward<F>(f)(Get<TLeft>()); }
    
    template<class F>
    void OnLeft(F&& f) const { if (IsLeft()) std::forward<F>(f)(Get<TLeft>()); }
    
    template<class F>
    void OnRight(F&& f){ if (IsRight()) std::forward<F>(f)(Get<TRight>()); }
    
    template<class F>
    void OnRight(F&& f) const { if (IsRight()) std::forward<F>(f)(Get<TRight>()); }
    
    template<class F, class T>
    typename std::result_of<F(TLeft const&)>::type OnLeft(F&& f, T&& otherwise) const
    {
		typedef typename std::result_of<F(TLeft const&)>::type result;
        static_assert(std::is_convertible<T, result>(),
            "Either<L, R>::OnLeft incompatible default and functor result");

		if (IsLeft())
			return std::forward<F>(f)(Get<TLeft>());
        return std::forward<T>(otherwise);
    }
    
    template<class F, class T>
    typename std::result_of<F(TRight const&)>::type OnRight(F&& f, T&& otherwise) const
    {
		typedef typename std::result_of<F(TRight const&)>::type result;
        static_assert(std::is_convertible<T, result>(),
            "Either<L, R>::OnRight incompatible default and functor result");

		if (IsRight())
			return std::forward<F>(f)(Get<TRight>());
        return std::forward<T>(otherwise);
    }

private:
    template<class T>
    T& Get(){ return reinterpret_cast<T&>(m_storage); }

    template<class T>
    T const& Get() const { return reinterpret_cast<T const&>(m_storage); }
    
    template<class T, class U>
    void Make(U&& source)
    {
        typedef typename std::remove_const<T>::type type;
        ::new ((void*)&m_storage) type(std::forward<U>(source));
    }
    
    void Destroy()
    {
        auto const state = m_state;
        m_state = State::uninitialised;
        
        if (state == State::left)
            Get<TLeft>().~TLeft();
        else if (state == State::right)
            Get<TRight>().~TRight();
    }

    static std::size_t const size = (sizeof(TLeft) > sizeof(TRight) ? sizeof(TLeft) : sizeof(TRight));
	static std::size_t const align_left = std::alignment_of<TLeft>::value;
	static std::size_t const align_right = std::alignment_of<TRight>::value;
    static std::size_t const align = (align_left > align_right ? align_left : align_right);
	typedef typename std::aligned_storage<size, align>::type storage_type;
    
	storage_type m_storage;
	State m_state;
};

template<class L, class R>
Either<L, R> MakeEither(bool isLeft, L&& leftVal, R&& rightVal)
{
	if (isLeft) return Either<L, R>(left, std::forward<L>(leftVal));
	return Either<L, R>(right, std::forward<R>(rightVal));
}

} // Util::

#include <iostream>

int main()
{
    Util::Either<int, double> a(Util::left, 21), b(Util::right, 20.);
    auto r = b.OnRight([](int i){ return i * 2; }, 10);
    a = b;
    std::cout << r << "\n";
}
