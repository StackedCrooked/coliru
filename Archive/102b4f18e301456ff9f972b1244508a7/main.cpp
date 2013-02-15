struct PT {
  template <typename T>
  struct traits {
    int c;
  };
};

template <template <typename K> class C>
struct A {
  typedef C<int> type;
  type b;
};

template <typename Pattern_Type, typename U>
void setup(Pattern_Type &halo_exchange) {
  A<Pattern_Type::template traits> a; // What is the name of Type::template construct?
  a.b.c=10;
}

int main() {
  A<PT::traits> a;

  a.b.c=10;

  return 0;
}