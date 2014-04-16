struct D
{
  template <class T> D (T);
};
int operator~(const D &);

template <typename T> T &make ();

template <typename Rhs> struct H
{
  static const int value = sizeof ~make<Rhs>();
};

enum class E;

int main () { return H<E>::value; }