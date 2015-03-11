  template <class U, enable_if_t<!is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value>>
  explicit constexpr propagate_const(propagate_const<U>&& pu) 
      : t_(std::move(get_underlying(pu)))
  {
  }

  template <class U, enable_if_t<is_convertible<U&&, T>::value &&
                                 is_constructible<T, U&&>::value>>
  constexpr propagate_const(propagate_const<U>&& pu) 
      : t_(std::move(get_underlying(pu)))
  {
  }