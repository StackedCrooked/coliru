#include "/Archive2/a9/4dd45fec6d529c/main.cpp"
#include <iostream>

template<class F>
void print_result_of (F&& cb) {
  auto res = (cb (), _or, "void");

  std::cout << "result: " << res << std::endl;
}

void  f () { }
int   g () { return 123; }
float h () { return 3.14f; }

int main () {
  print_result_of (f);
  print_result_of (g);
  print_result_of (h);
}
