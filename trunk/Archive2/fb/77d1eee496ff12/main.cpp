template<typename T>
bool foo(T * begin, T * end) {
  if (begin == end)
    return false;

  T a, b;
  bool first = true, second = true;
  bool comp_b = false;

  for (T* it = begin; it != end; ++it) {
    T value = *it;
    if (first) {
      a = *it;
      first = false;
      continue;
    }   

    if (!first && second) {
      if (value == a) return false;
      second = false;
      b = *it;
      continue;
    }   

    if (value == a || value == b) {
      if (comp_b) {
        if (value != b)
          return false;
        else
          comp_b = false;
      }   
      else {
        if (value != a)
          return false;
        else
          comp_b = true;
      }   
    }   
    else {
      return false;
    }   
  }

  return !second;
}