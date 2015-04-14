template<int N>
struct ic {
  constexpr int value () const {
    return N;
  }
};

int main () {
  auto foo = [] (auto d) {
    using A = ic<d.value ()>;

    []() { A {}; }; // <- segfault
  };

  foo (ic<1> {});
}