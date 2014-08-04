struct S {
  template <typename Ty = char>
  static_assert(sizeof(Ty) != 1, "Not a char");
};

int main() {}