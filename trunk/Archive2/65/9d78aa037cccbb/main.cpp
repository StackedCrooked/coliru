  template <class U,
            class V = enable_if_t<!is_convertible<U&&, T>::value &&
                                  is_constructible<T, U&&>::value &&
                                  !is_propagate_const<decay_t<U>>::value> >
  explicit constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }

  template <class U,
            class V = enable_if_t<is_convertible<U&&, T>::value &&
                                  is_constructible<T, U&&>::value &&
                                  !is_propagate_const<decay_t<U>>::value> >
  constexpr propagate_const(U&& u)
      : t_(std::forward<U>(u))
  {
  }