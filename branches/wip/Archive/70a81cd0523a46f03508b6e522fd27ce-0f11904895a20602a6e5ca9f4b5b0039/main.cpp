#include <cassert> 
#include <iostream>



struct Default{};


struct Upper
{
    template<typename T>
    T apply_bound(T b, const T& max) const
    {
        if (b > max) return max;
        else return b;
    }
};

struct Lower
{
    template<typename T>
    T apply_bound(T b, const T& min) const
    {
        if (b < min) return min;
        return b;
    }
};


template<typename T, typename Impl>
struct GenericBound : Impl
{
    GenericBound(T b) : bound(b) {}
    
    T apply(T t) const
    {
        return this->apply_bound(t, bound);
    }
    
    T bound;
};

template<typename T> using UpperBound = GenericBound<T, Upper>;
template<typename T> using LowerBound = GenericBound<T, Lower>;



// 
// enable (LowerBound<T>{a} && UpperBound<T>{t})
//
template<typename T, typename A, typename B>
struct Combine
{
    Combine(const GenericBound<T, A>& a, const GenericBound<T, B>& b) : a(a), b(b) {}
    
    T apply(T t) const
    {
        return b.apply(a.apply(t));
    }
    
    GenericBound<T, A> a;
    GenericBound<T, B> b;
};

template<typename T, typename A, typename B>
auto operator&& (GenericBound<T, A> a, GenericBound<T, B> b)
{
    return Combine<T, A, B>{a, b};
}



//
// functor factory functions
//
template<typename T>
auto upper(T t, T initial = T())
{
    return GenericBound<T, Upper>{t};
}
template<typename T>
auto lower(T t, T initial = T())
{
    return GenericBound<T, Lower>{t};
}

template<typename T, typename U>
void set(T& t, U u)
{
    std::cout << t << " + " << u << " = " << (t = u) << std::endl;
}


int main()
{
    auto combo = lower(100) && upper(500);
    
    std::cout << combo.apply(99) << std::endl;
    std::cout << combo.apply(100) << std::endl;
    std::cout << combo.apply(101) << std::endl;
    
    std::cout << combo.apply(499) << std::endl;
    std::cout << combo.apply(500) << std::endl;
    std::cout << combo.apply(501) << std::endl;
}




