struct magic {
  template<class T>
  struct hack {
    hack (T&& ref) : _ref (static_cast<T&&> (ref)) { }

    template<class U>
    T&& operator, (U&&) { typedef T T2;
      return  static_cast<T2&&> (_ref); // gcc-bug https://gcc.gnu.org/bugzilla/show_bug.cgi?id=57063
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