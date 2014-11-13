template <int year>
class Model8556
{
private: 

  static const int yearMax = 2000; // I assume you meant a static constant
  static const int yearMin = 1990;

  static_assert( yearMin <= year && year <= yearMax,        // Condition
                 "Invalid template argument specified!" );  // Error message
};

template class Model8556<1990>;
template class Model8556<1997>;
template class Model8556<1980>; // Fails

int main() {}