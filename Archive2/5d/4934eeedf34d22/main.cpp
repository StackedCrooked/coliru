#include <type_traits>
#include <utility>
#include <new>

namespace EitherDetail
{    
template<class CallSig, class = void>
struct result_of{};

template<class F, class A1>
struct result_of<F(A1), decltype(std::declval<F>()(std::declval<A1>()), void())>
{
    typedef decltype(std::declval<F>()(std::declval<A1>())) type;
};
} // EitherDetail::

static struct left_tag{} const left = {};
static struct right_tag{} const right = {};

template<class TLeft, class TRight>
class Either
{
public:    
    template<class T>
    Either(left_tag, T&& v)
        : m_isLeft(true)
    {
        Make<TLeft>(std::forward<T>(v));
    }
    
    template<class T>
    Either(right_tag, T&& v)
        : m_isLeft(false)
    {
        Make<TRight>(std::forward<T>(v));
    }
    
    Either(Either const& other)
        : m_isLeft(other.m_isLeft)
    {
        if (m_isLeft) Make<TLeft>(other.Get<TLeft>());
        else Make<TRight>(other.Get<TRight>());
    }
    
    Either(Either&& other)
        : m_isLeft(other.m_isLeft)
    {
        if (m_isLeft) Make<TLeft>(std::move(other.Get<TLeft>()));
        else Make<TRight>(std::move(other.Get<TRight>()));
    }
    
    ~Either(){ Destroy(); }
    
    Either& operator=(Either other)
    {
        Destroy();
        
        m_isLeft = other.m_isLeft;
        if (m_isLeft) Make<TLeft>(std::move(other.Get<TLeft>()));
        else Make<TRight>(std::move(other.Get<TRight>()));
    }
    
    template<class FL, class FR,
        class NewLeft = typename std::result_of<FL(TLeft const&)>::type,
        class NewRight = typename std::result_of<FR(TRight const&)>::type>
    NewLeft FanIn(FL&& fl, FR&& fr) const
    {
        static_assert(std::is_same<NewLeft, NewRight>(),
            "Either<L, R>::FanIn functors need to return the same type");
            
        if (m_isLeft) return std::forward<FL>(fl)(Get<TLeft>());
        else return std::forward<FR>(fr)(Get<TRight>());
    }
    
    template<class F, class T,
        class Result = typename EitherDetail::result_of<F(TLeft const&)>::type>
    Result OnLeft(F&& f, T&& otherwise) const
    {
        static_assert(std::is_convertible<T, Result>(),
            "Either<L, R>::OnLeft incompatible default and functor result");
        return On<TLeft, Result>(std::forward<F>(f), std::forward<T>(otherwise), m_isLeft);
    }
    
    template<class F, class T,
        class Result = typename EitherDetail::result_of<F(TRight const&)>::type>
    Result OnRight(F&& f, T&& otherwise) const
    {
        static_assert(std::is_convertible<T, Result>(),
            "Either<L, R>::OnRight incompatible default and functor result");
        return On<TRight, Result>(std::forward<F>(f), std::forward<T>(otherwise), !m_isLeft);
    }

private:
    template<class T>
    T& Get(){ return reinterpret_cast<T&>(m_storage); }

    template<class T>
    T const& Get() const { return reinterpret_cast<T const&>(m_storage); }
    
    template<class T, class U>
    void Make(U&& source){ ::new ((void*)&m_storage) T(std::forward<U>(source)); }
    
    template<class T, class Result, class F, class U>
    Result On(F&& f, U&& otherwise, bool condition) const
    {  
        if (condition) return std::forward<F>(f)(Get<T>());
        else return std::forward<U>(otherwise);
    }
    
    void Destroy()
    {
        if (m_isLeft) Get<TLeft>().~TLeft();
        else Get<TRight>().~TRight();
    }

    static unsigned const size = (sizeof(TLeft) > sizeof(TRight) ? sizeof(TLeft) : sizeof(TRight));
    static unsigned const align = (alignof(TLeft) > alignof(TRight) ? alignof(TLeft) : alignof(TRight));
	typedef typename std::aligned_storage<size, align>::type storage_type;
    
    storage_type m_storage;
    bool m_isLeft;
};

#include <iostream>

int main()
{
    Either<int, double> a(left, 21), b(right, 20.);
    auto r = b.OnRight([](int i){ return i * 2; }, 10);
    std::cout << r << "\n";
}
