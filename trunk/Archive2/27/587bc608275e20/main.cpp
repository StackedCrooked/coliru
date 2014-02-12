    int const x = 10; // implementation stores to read-only memory
                      // implementation crashes on writes to read-only memory

    void foo(int const **ptr) {
      *ptr = &x;
    }

    int main() {
      int *p;
      foo(const_cast<int const **>(&p));
      *p = 12; // crash
    }
