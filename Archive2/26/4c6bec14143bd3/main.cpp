#include <type_traits>
#include <utility>
#include <iterator>
#include <cstdint>
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>

#define sgi_assert(cond)     ((void)0)

namespace sgi { namespace detail
{


template<typename T>
struct remove_cvr : std::remove_cv<std::remove_reference_t<T>> {};


template<typename T>
using remove_cvr_t = typename remove_cvr<T>::type;


template<typename T>
class is_iterable_container
{
    template<typename U>
    static auto check(U&) -> decltype(std::begin(std::declval<U&>()) != std::end(std::declval<U&>()), std::uint8_t(0))
    {
        return 0;
    }
    static std::uint16_t check(...)
    {
        return 0;
    }
public:
	static constexpr bool value = sizeof(check(std::declval<remove_cvr_t<T>&>())) < sizeof(std::uint16_t); //!< true if T is iterable. false if T otherwise
};

template<typename T>
class is_contiguous_container
{
    template<typename U>
    static auto check(U&) -> decltype(std::declval<U&>().data(), std::declval<U&>().size(), std::enable_if_t<std::is_pointer<decltype(std::declval<U&>().data())>::value>(0), std::uint8_t(0))
    {
        return 0;
    }
    static std::uint16_t check(...)
    {
        return 0;
    }
public:
	static constexpr bool value = sizeof(check(std::declval<remove_cvr_t<T>&>())) < sizeof(std::uint16_t); // true if T is iterable. false if T otherwise
};


template<typename T, bool Iterable> // T any type. Iterable==true if T is iterable false otherwise
struct value_type_of_imp
{
    // Iterable is true here
    using type = remove_cvr_t<decltype(*std::begin(std::declval<T&>()))>; //!< value_type of values in T if T is iterable. value_type is the same as T otherwise
};
template<typename T>
struct value_type_of_imp<T, false>
{
    using type = T; //!< value_type of values in T if T is iterable. value_type is the same as T otherwise
};

template<typename T>
using value_type_of_t = typename value_type_of_imp<T, is_iterable_container<T>::value>::type;


}}


namespace sgi
{

/**
* @brief trait to check if a type can be used with std::being and std::end
* @tparam T any type
*/
template<typename T>
struct is_iterable_container : detail::is_iterable_container<T> {};

/**
* @brief trait to check if a type has the methods data() and size()
* @tparam T any type
* @note concept contiguous_container: a container with values in contiguous memory with a pointer accessed through data() and the number of values is queried with size()
* @note the trait only checks the methods data() and size() without a guaranties whether the memory is contiguous or not
*/
template<typename T>
struct is_contiguous_container : detail::is_contiguous_container<T> {};

/**
* @brief remove a reference if it exists then remove a const or a volatile if one exists
* @tparam T any type
*/
template<typename T>
using remove_cvr = detail::remove_cvr<T>;

/**
* @brief equivalent to typename detail::remove_cvr<T>::type
* @tparam T any type
*/
template<typename T>
using remove_cvr_t = detail::remove_cvr_t<T>;

/** 
* @brief return the value_type of values of an iterable sequence. If the type is not iterable the value type remains the same
* @tparam T any typename
*/
template<typename T>
using value_type_of_t = detail::value_type_of_t<T>;


} // namespace





/**
* @file      math.hpp
* @author    alasram
* @brief     general math functions
* @copyright 2014
*/


#ifndef SGI_MATH_MATH_HPP
#define SGI_MATH_MATH_HPP

namespace sgi
{


/** 
* @brief convert degrees to radians
* @param x angle in degrees
* @tparam T floating point typename
* @return angle in radians
*/
template<typename T>
T radians(T x);

/** 
* @brief convert radians to degrees
* @param x angle in radians
* @tparam T floating point typename
* @return angle in degrees
*/
template<typename T>
T degrees(T x);

/** 
* @brief extract the sign
* @param x arithmetic value
* @tparam T signed arithmetic typename
* @return 1 if x > 0, 0 if x == 0, or -1 if x < 0
*/
template<typename T>
T sign(T x);

/** 
* @brief fractional part
* @param x floating point value
* @tparam T floating point typename (an error is triggered otherwise)
* @return fractional part of x
*/
template<typename T>
T frac(T x);

/** 
* @brief alias to frac
* @param x floating point value
* @tparam T floating point typename (an error is triggered otherwise)
* @return fractional part of x
*/
template<typename T>
T fract(T x);

/** 
* @brief clamp x to range [mini, maxi]
* @param x value to clamp
* @param mini range start
* @param maxi range end. UB if(mini > maxi)
* @tparam T comparable non iterable typename
* @tparam U comparable non iterable typename. std::common_type<T,U>::type must be T
* @return clamped x
*/
template<typename T, typename U>
typename std::enable_if<!is_iterable_container<T>::value && !is_iterable_container<U>::value, T>::type clamp(T x, U mini, U maxi);

/** 
* @brief clamp x to range [mini, maxi]
* @param x value to clamp
* @param mini range start
* @param maxi range end. UB if(mini > maxi)
* @tparam T iterable type with a comparable value_type
* @tparam U non iterable comparable type
* @return clamped x
*/
template<typename T, typename U>
typename std::enable_if<is_iterable_container<T>::value && !is_iterable_container<U>::value, T>::type clamp(T x, U mini, U maxi);

/** 
* @brief clamp x to range [0, 1]
* @param x value to be clamped
* @tparam T float typename
* @return saturated x
*/
template<typename T>
T saturate(T x);

/** 
* @brief wrap value in [0,1[ ex wrap(2.1) -> 0.1 and wrap(-0.1) -> 0.9
* @param x value to wrapped
* @tparam T floating point typename
* @return wrapped x
*/
template<typename T>
T wrap(T x);

/** 
* @brief wrap value in range R. R=[0,n[
* @param x value to wrapped
* @param n wrapping range
* @tparam T floating point or integral typename
* @return wrapped x
*/
template<typename T>
T wrap(T x, T n);

/** 
* @brief vector dot product
* @param a first vector operand (any iterable type)
* @param b second vector operand. must have the same size as a
* @tparam V iterable type
* @return dot product result
*/
template<typename V>
auto dot(V const& x, V const& y) -> remove_cvr_t<decltype(*std::begin(x))>;

/** 
* @brief vector squared length
* @param v vector
* @tparam V iterable type
* @return vector squared length result
*/
template<typename V>
auto square_length(V const& v) -> decltype( dot(v,v) );

/** 
* @brief vector length
* @param v vector
* @tparam V iterable type
* @return vector length result
*/
template<typename V>
auto length(V const& v) -> decltype(std::sqrt(square_length(v)));

/** 
* @brief squared distance between 2 points
* @param x first point
* @param y second point, must have the same size as x
* @tparam V iterable type with value_type supporting operator-
* @return squared distance between x and y
*/
template<typename V>
auto square_distance(V const& x, V const& y) -> remove_cvr_t<decltype(*std::begin(x))>;

/** 
* @brief distance between 2 points
* @param x first point
* @param y second point
* @tparam V iterable type with value_type supporting operator-
* @return distance between x and y
*/
template<typename V>
auto distance(V const& x, V const& y) -> decltype(std::sqrt(square_distance(x,y)));

/** 
* @brief vector normalization
* @param v vector
* @tparam V copyable iterable type different from a static array
* @return unit vector with same direction/orientation as v
*/
template<typename V>
V normalize(V const& v);

/** 
* @brief linear interpolation
* @param x starting point of the linear curve
* @param y ending point of the linear curve
* @param a interpolation factor: must be between 0 and 1
* @tparam T arithmetic typename
* @return linear interpolation between x and y with scalar factor a
*/
template<typename T>
T lerp(T const& x, T const& y, T const& a);

/** 
* @brief linear interpolation
* @param x starting point of the linear curve
* @param y ending point of the linear curve
* @param a interpolation factor: must be between 0 and 1
* @tparam V copyable iterable type with value_type T
* @tparam T arithmetic typename
* @return linear interpolation between x and y with scalar factor a
*/
template<typename V, typename T>
V lerp(V const& x, V const& y, T const& a);

/** 
* @brief step if x reaches y 
* @param x any position
* @param y step position
* @tparam T arithmetic typename
* @return T(0) if x<y, T(1) otherwise
*/
template<typename T>
T step(T y, T x);

/** 
* @brief pulse between y0 and y1
* @param x any position
* @param y0 pulse start
* @param y1 pulse end
* @tparam T arithmetic typename
* @return T(1) if y0 <= x <= y1, T(0) otherwise
*/
template<typename T>
T pulse(T y0, T y1, T x);

/** 
* @brief smooth t using s-curve Perlin noise function
* @param t value between 0 and 1
* @tparam T arithmetic typename
* @return 3*t*t - 2*t*t*t
*/
template<typename T>
T smooth(T t);

/** 
* @brief smoth t using s-curve Improved Perlin noise function
* @param t value between 0 and 1
* @tparam T arithmetic typename
* @return 6*t*t*t*t*t - 15*t*t*t*t + 10*t*t*t
*/
template<typename T>
T ismooth(T t);

/** 
* @brief smoothly step from y0 to y1
* @param x any position
* @param y0 smooth stepping starting position
* @param y1 smooth stepping ending position
* @tparam T arithmetic typename
* @return T(0) if x<y0, T(1) if x>y1, smooth((x-y0)/(y1-y0)) otherwise
*/
template<typename T>
T smoothstep(T y0, T y1, T x);

/** 
* @brief smoothly step from y0 to y1
* @param x any position
* @param y0 smooth stepping starting position
* @param y1 smooth stepping ending position
* @tparam T arithmetic typename
* @return T(0) if x<y0, T(1) if x>y1, ismooth((x-y0)/(y1-y0)) otherwise
*/
template<typename T>
T ismoothstep(T y0, T y1, T x);

} // namespace

#endif // include guard


/**
* @file      math.hpp
* @author    alasram
* @brief     general math functions
* @copyright 2014
*/


#ifndef SGI_MATH_MATH_IPP
#define SGI_MATH_MATH_IPP

#include <functional>
#include <algorithm>
#include <cmath>
#include <boost/math/constants/constants.hpp>

namespace sgi { namespace detail
{

template<typename T, bool>
struct wrap
{
    static T call(T x, T n)
    {
		static_assert(std::is_floating_point<T>::value, "T must be a floating point typename");
        return fmod(fmod(x, n) + n, n);
    }
};

template<typename T>
struct wrap<T,false>
{
	static T call(T x, T n)
    {
		static_assert(std::is_integral<T>::value, "T must be an integral typename");
		using type = typename std::make_unsigned<T>::type;
        return type(x) % type(n);
    }
};


}} // namespace

namespace sgi
{




template<typename T>
T sign(T x)
{
	static_assert(std::is_signed<T>::value, "T must be a signed arithmetic typename");
	return x > T(0) ? T(1) : (x==T(0) ? T(0) : T(-1));
}


template<typename T>
T frac(T x)
{
	static_assert(std::is_floating_point<T>::value, "T must be a floating point typename");
	return x - std::floor(x);
}


template<typename T>
T fract(T x)
{
	return frac(x);
}


template<typename T, typename U>
typename std::enable_if<!is_iterable_container<T>::value && !is_iterable_container<U>::value, T>::type clamp(T x, U mini, U maxi)
{
	sgi_assert(mini <= maxi);
    static_assert(std::is_same<typename std::common_type<T,U>::type, T>::value, "T must be the common type");
	return std::min(std::max(x, T(mini)), T(maxi));
}


template<typename T, typename U>
typename std::enable_if<is_iterable_container<T>::value && !is_iterable_container<U>::value, T>::type clamp(T x, U mini, U maxi)
{
    std::transform(std::begin(x), std::end(x), std::begin(x), [mini, maxi](value_type_of_t<T> x){return clamp(x, mini, maxi);});
    return x;
}


template<typename T>
T saturate(T x)
{
	return clamp(x, T(0), T(1));
}


template<typename T>
T wrap(T x)
{
	return detail::wrap<T,true>::call(x, T(1));
}


template<typename T>
T wrap(T x, T n)
{
    return detail::wrap<T,std::is_floating_point<T>::value>::call(x, n);
}


template<typename V>
auto dot(V const& x, V const& y) -> remove_cvr_t<decltype(*std::begin(x))>
{
	static_assert(is_iterable_container<V>::value, "V must be an iterable type");
    sgi_assert( std::distance(std::begin(x), std::end(x)) == std::distance(std::begin(y), std::end(y)) );
    return std::inner_product(std::begin(x), std::end(x), std::begin(y), remove_cvr_t<decltype(*std::begin(x))>(0));
}


template<typename V>
auto square_length(V const& v) -> decltype(dot(v,v) )
{
	return dot(v,v);
}


template<typename V>
auto length(V const& v) -> decltype(std::sqrt(square_length(v)))
{
    return std::sqrt( square_length(v) );
}


template<typename V>
auto square_distance(V const& x, V const& y) -> remove_cvr_t<decltype(*std::begin(x))>
{
	static_assert(is_iterable_container<V>::value, "V must be an iterable type");
    sgi_assert( std::distance(std::begin(x), std::end(x)) == std::distance(std::begin(y), std::end(y)) );
    using type = remove_cvr_t<decltype(*std::begin(x))>;
	return std::inner_product(std::begin(x), std::end(x), std::begin(y), type(0), std::plus<type>(), [](type const& x, type const& y){ return (x-y)*(x-y); });
}


template<typename V>
auto distance(V const& x, V const& y) -> decltype(std::sqrt(square_distance(x,y)))
{
	return std::sqrt(square_distance(x,y));
}


template<typename V>
V normalize(V const& v)
{
	static_assert(is_iterable_container<typename std::decay<V>::type>::value, "V must be an iterable type different from a static array"); // the decay eleminates the static array
    static_assert(std::is_copy_constructible<V>::value, "V must be copyable");
    V r(v);
    auto l = square_length(r);
    using value_type = typename std::decay<decltype(l)>::type;
    sgi_assert( l >= value_type(0) );
    l = value_type(1) / std::sqrt(l);
    for(auto& i : r)
        i *= l;
    return r;
}


template<typename T>
T lerp(T const& x, T const& y, T const& a)
{
	sgi_assert( a >= T(0) && a <= T(1) );
	return x + a * (y - x);
}


template<typename V, typename T>
V lerp(V const& x, V const& y, T const& a)
{
	static_assert(is_iterable_container<V>::value, "V must be an iterable type");
    static_assert(std::is_same<value_type_of_t<V>, T>::value, "V value_tpe must be the same as T");
    static_assert(std::is_copy_constructible<V>::value, "V must be copyable");
    sgi_assert( std::distance(std::begin(x), std::end(x)) == std::distance(std::begin(y), std::end(y)) );
    V r(x);
    std::transform(std::begin(r), std::end(r), std::begin(y), std::begin(r), std::bind(lerp<T>, std::placeholders::_1, std::placeholders::_2, a));
	return r;
}


template<typename T>
T step(T y, T x)
{
	static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic typename");
	return static_cast<T>(x >= y);
}


template<typename T>
T pulse(T y0, T y1, T x)
{
	return step(y0,x) - step(y1,x);
}


template<typename T>
T smooth(T t)
{
	sgi_assert( t >= T(0) && t <= T(1) );
	return t * t * (T(3) - T(2) * t);
}


template<typename T>
T ismooth(T t)
{
	sgi_assert( t >= T(0) && t <= T(1) );
	return t * t * t * (t * (t * T(6) - T(15)) + T(10));
}


template<typename T>
T smoothstep(T y0, T y1, T x)
{
	sgi_assert( y0 != y1 );
	return smooth( clamp( (x-y0)/(y1-y0), T(0), T(1) ) );
}


template<typename T>
T ismoothstep(T y0, T y1, T x)
{
	sgi_assert( y0 != y1 );
	return ismooth( clamp( (x-y0)/(y1-y0), T(0), T(1) ) );
}

} // namespace

#endif // include guard






int main()
{
    using namespace sgi;
    std::cout << wrap(3.14f, 2.f) << std::endl;
    return 0;
    // std::cout << sgi::clamp(3, 5, 10) << std::endl;
    std::vector<int> vec = {0,1,2,3,4,5,6,7,8,9};
    std::vector<int> vecc =  sgi::clamp(vec, short(3), short(7));
    std::cout << "norm = " << sgi::dot(vec, vec) << std::endl;
    for(auto v : vecc)
    {
        std::cout << sgi::pulse(4,6,v) << std::endl;
    }
}
