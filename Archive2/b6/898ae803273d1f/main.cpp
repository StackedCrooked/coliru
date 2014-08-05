enum E { foo };

struct C {
  operator E() const { return foo; }
  operator E() { return foo; }
};

int main() {
  C c;
  switch (c) {
    case foo: break;
  }
}