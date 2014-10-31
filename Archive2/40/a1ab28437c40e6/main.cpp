#include <type_traits>
#include <utility>
#include <new>
#include <stdexcept>
#include <cstddef>
#include <cassert>

namespace Util
{

namespace EitherDetail
{
template<class T> T&& declval();

template<class CallSig, class = void>
struct result_of{};

template<class F, class A1>
struct result_of<F(A1), decltype(declval<F>()(declval<A1>()), void())>
{
    typedef decltype(declval<F>()(declval<A1>())) type;
};
} // EitherDetail::

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
        : m_state(State::uninitialised)
    {
        Make<TLeft>(std::forward<T>(v));
        m_state = State::left;
    }
    
    template<class T>
    Either(right_tag, T&& v)
        : m_state(State::uninitialised)
    {
        Make<TRight>(std::forward<T>(v));
        m_state = State::right;
    }
    
    Either(Either const& other)
        : m_state(State::uninitialised)
    {
        if (other.m_state == State::left)
            Make<TLeft>(other.Get<TLeft>());
        else if (other.m_state == State::right)
            Make<TRight>(other.Get<TRight>());
        m_state = other.m_state;
    }
    
    Either(Either&& other)
        : m_state(State::uninitialized)
    {
        if (other.m_state == State::left)
            Make<TLeft>(std::move(other.Get<TLeft>()));
        else if (other.m_state == State::right)
            Make<TRight>(std::move(other.Get<TRight>()));
        m_state = other.m_state;
    }
    
    ~Either(){ Destroy(); }
    
    Either& operator=(Either other)
    {
        Destroy();
        
        if (other.m_state == State::left)
            Make<TLeft>(std::move(other.Get<TLeft>()));
        else if (other.m_state == State::right)
            Make<TRight>(std::move(other.Get<TRight>()));
        m_state = other.m_state;
    }
    
    template<class FL, class FR>
    typename EitherDetail::result_of<FL(TLeft const&)>::type Merge(FL&& onLeft, FR&& onRight) const
    {
    	typedef typename EitherDetail::result_of<FL(TLeft const&)>::type left_result;
        typedef typename EitherDetail::result_of<FR(TRight const&)>::type right_result;
        static_assert(std::is_same<left_result, right_result>(),
            "Either<L, R>::Merge functors need to return the same type");
            
        assert(m_state != State::uninitialised);
        if (m_state == State::left)
            return std::forward<FL>(onLeft)(Get<TLeft>());
        else if (m_state == State::right)
            return std::forward<FR>(onRight)(Get<TRight>());
        throw std::runtime_error("Either<L, R>::Merge used after destruction");
    }
    
    template<class F, class T>
    typename EitherDetail::result_of<F(TLeft const&)>::type OnLeft(F&& f, T&& otherwise) const
    {
		typedef typename EitherDetail::result_of<F(TLeft const&)>::type result;
        static_assert(std::is_convertible<T, result>(),
            "Either<L, R>::OnLeft incompatible default and functor result");
        return On<TLeft, result>(std::forward<F>(f), std::forward<T>(otherwise), State::left);
    }
    
    template<class F, class T>
    typename EitherDetail::result_of<F(TRight const&)>::type OnRight(F&& f, T&& otherwise) const
    {
		typedef typename EitherDetail::result_of<F(TRight const&)>::type result;
        static_assert(std::is_convertible<T, result>(),
            "Either<L, R>::OnRight incompatible default and functor result");
        return On<TRight, result>(std::forward<F>(f), std::forward<T>(otherwise), State::right);
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
    
    template<class T, class Result, class F, class U>
    Result On(F&& f, U&& otherwise, State target) const
    {  
        if (m_state == target) return std::forward<F>(f)(Get<T>());
        else return std::forward<U>(otherwise);
    }
    
    void Destroy()
    {
        auto state = m_state;
        m_state = State::uninitialised;
        
        if (state == State::left)
            Get<TLeft>().~TLeft();
        else if (state == State::right)
            Get<TRight>().~TRight();
    }

    static std::size_t const size = (sizeof(TLeft) > sizeof(TRight) ? sizeof(TLeft) : sizeof(TRight));
    static std::size_t const align = (alignof(TLeft) > alignof(TRight) ? alignof(TLeft) : alignof(TRight));
	typedef typename std::aligned_storage<size, align>::type storage_type;
    
    storage_type m_storage;
	State m_state;
};

} // Util::

#include <iostream>

int main()
{
    Util::Either<int, double> a(Util::left, 21), b(Util::right, 20.);
    auto r = b.OnRight([](int i){ return i * 2; }, 10);
    std::cout << r << "\n";
}
