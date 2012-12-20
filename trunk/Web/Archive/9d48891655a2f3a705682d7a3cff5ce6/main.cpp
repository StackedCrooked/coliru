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
  A<Pattern_Type::template traits> a; // Line 17: Comment this
  a.b.c=10; // Comment this
}

int main() {
  A<PT::traits> a;

  a.b.c=10;

  return 0;
}