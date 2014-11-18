#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <limits>

// type alias used to simplify the syntax of std::enable_if
template <typename T>
using Invoke = typename T::type;

template <typename Condition>
using EnableIf = Invoke < std::enable_if<Condition::value> >;

template <typename T>
struct Identity
{
    typedef T type;
};

template <typename T>
struct RemoveConstRef
: std::remove_reference<typename std::remove_const<T>::type>
{};

template <typename T, typename Enable = void>
struct MakeUnsigned 
: Identity<T>
{};
template <typename T>
struct MakeUnsigned<T, typename std::enable_if< std::is_integral<T>::value >::type>
: std::make_unsigned<T>
{};
template <typename T, typename U, typename Enable = void>
struct ShouldUseAnsiConversion : std::false_type {};
template <typename T, typename U>
struct ShouldUseAnsiConversion 
<
    T          
  , U
  , typename std::enable_if
    <
        std::is_same<typename RemoveConstRef<T>::type, typename RemoveConstRef<U>::type>::value ||
        std::numeric_limits<T>::is_signed == std::numeric_limits<U>::is_signed ||
        std::is_floating_point<T>::value ||
        std::is_floating_point<U>::value
    >::type
> : std::true_type{};
template <typename T, typename U, typename Enable = void>
struct ShouldConvertToUnsignedT : std::false_type {};
template <typename T, typename U>
struct ShouldConvertToUnsignedT
<
    T
  , U
  , typename std::enable_if
    <
        !std::is_same<typename RemoveConstRef<T>::type, typename RemoveConstRef<U>::type>::value &&
        std::numeric_limits<T>::is_signed != std::numeric_limits<U>::is_signed &&
        std::is_integral<T>::value &&
        std::is_integral<U>::value &&
        sizeof(U) < sizeof(T)
    >::type
> : std::true_type{};
template <typename T, typename U, typename Enable = void>
struct ShouldConvertToUnsignedU : std::false_type {};
template <typename T, typename U>
struct ShouldConvertToUnsignedU
<
    T
  , U
  , typename std::enable_if
    <
        !std::is_same<typename RemoveConstRef<T>::type, typename RemoveConstRef<U>::type>::value &&
        std::numeric_limits<T>::is_signed != std::numeric_limits<U>::is_signed &&
        std::is_integral<U>::value &&
        std::is_integral<T>::value &&
        sizeof(U) >= sizeof(T)
    >::type
> : std::true_type{};
//! Same type or both signed or one is a floating point (let default casting deal with it) - return arg by ref
template 
<
    typename T
  , typename U
  , typename Arg
  , typename = Invoke<ShouldUseAnsiConversion<T, U>>
>
inline const Arg& SafeCmpCast(const Arg& u)
{
    return u;
}
//! Same type or both signed or one is a floating point (let default casting deal with it) - return arg by ref
template 
<
    typename T
  , typename U
  , typename Arg
  , typename = Invoke<ShouldUseAnsiConversion<T, U>>
>
inline Arg SafeCmpCast(Arg&& u)
{
    return u;
}
//! Not the same type, T is wider and is not signed, the other is.
//! Safe to convert to T.
template 
<
    typename T
  , typename U
  , typename Arg
  , typename = Invoke<ShouldConvertToUnsignedT<T, U>>
>
inline typename MakeUnsigned<T>::type SafeCmpCast(const Arg& u)
{
    return static_cast<typename MakeUnsigned<T>::type>(u);
}
//! Not the same type, U is wider and is not signed, the other is.
//! Safe to convert to U.
template
<
    typename T
  , typename U
  , typename Arg
  , typename = Invoke<ShouldConvertToUnsignedU<T, U>>
>
inline typename MakeUnsigned<U>::type SafeCmpCast(const Arg& u)
{
    return static_cast<typename MakeUnsigned<U>::type>(u);
}

int main()
{
    static_assert(!ShouldUseAnsiConversion<unsigned int, int>::value, "Conversion should not be ansi.");
    static_assert(!ShouldConvertToUnsignedT<unsigned int, int>::value, "Conversion should not be down converted to int.");
    static_assert(ShouldConvertToUnsignedU<unsigned int, int>::value, "Conversion should be up converted to unsigned int.");    
    auto a = SafeCmpCast<unsigned int, int>(static_cast<unsigned int>(20));
    static_assert(std::is_same<decltype(a), unsigned int>::value, "Should be unsigned int.");
    std::cout << "Done." << std::endl;
    return 0;
}
