    int const x = 10; // implementation stores to read-only memory
                      // implementation crashes on writes to read-only memory

    void foo(int const * const *ptr) {
      *ptr = &x;
    }

    int main() {
      int *p;
      foo(&p);
      *p = 12; // crash
    }
