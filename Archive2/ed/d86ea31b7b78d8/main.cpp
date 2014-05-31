#include <functional>

namespace std {

    template <> struct plus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) + std::forward<U>(u));
    };
    
    template <> struct minus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) - std::forward<U>(u));
    };
    
    template <> struct multiplies<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) * std::forward<U>(u));
    };
    
    template <> struct divides<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) / std::forward<U>(u));
    };
    
    template <> struct modulus<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) % std::forward<U>(u));
    };
    
    template <> struct negate<void> {
      template <class T> auto operator()(T&& t) const
        -> decltype(-std::forward<T>(t));
    };
    
    template <> struct equal_to<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) == std::forward<U>(u));
    };
    
    template <> struct not_equal_to<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) != std::forward<U>(u));
    };
    
    template <> struct greater<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) > std::forward<U>(u));
    };
    
    template <> struct less<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) < std::forward<U>(u));
    };
    
    template <> struct greater_equal<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) >= std::forward<U>(u));
    };
    
    template <> struct less_equal<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) <= std::forward<U>(u));
    };
    
    template <> struct logical_and<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) && std::forward<U>(u));
    };
    
    template <> struct logical_or<void> {
      template <class T, class U> auto operator()(T&& t, U&& u) const
        -> decltype(std::forward<T>(t) || std::forward<U>(u));
    };
    
    template <> struct logical_not<void> {
      template <class T> auto operator()(T&& t) const
        -> decltype(!std::forward<T>(t));
    };
    
};