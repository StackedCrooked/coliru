struct magic {
  template<class T>
  struct hack {
    hack (T&& ref) : _ref (static_cast<T&&> (ref)) { } 

    template<class T1, class U>
    friend T1&& operator, (hack<T1> const& h, U&&) {
      return h._ref;
    }   

    T&& _ref;
  };  

  template<class T>
  friend hack<T> operator, (T&& val, magic) {
    return static_cast<T&&> (val);
  }

  template<class T>
  friend T&& operator, (magic, T&& val) {
    return static_cast<T&&> (val);
  }
};

namespace {
  magic _or;
}