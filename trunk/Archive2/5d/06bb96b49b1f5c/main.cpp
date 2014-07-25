struct AClass {
  AClass() = default;
};

struct BClass {
  BClass();
};

inline
BClass::BClass() = default;

int main() {
  const AClass a;
  const BClass b;
}