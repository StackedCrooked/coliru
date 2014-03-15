#include <iostream>

void print (void){}
template <typename... Tail>
void print (bool b, Tail... t);
template <typename Head, typename... Tail>
void print (Head h, Tail... t);


template <typename Head, typename... Tail>
void print (Head h, Tail... t) {
  std::cout << h << " ";
  print(t...);
}

template <typename... Tail>
void print (bool , Tail... t) {
  std::cout <<"bool" << " ";
  print(t...);
}

int main(int argc, char *argv[]) {
  print("string", 42, true, 3.43, true, 'c');
  return 0;
}