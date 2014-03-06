#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

// #include "some-header.tpp"

template<typename T>
void func () {
  T x;
}

#pragma clang diagnostic pop

int main () {
  func<int> ();
  int y;
}
