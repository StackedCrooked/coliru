template <typename Fn>
void foo(Fn F) {
  F();    
}

int main () {
  int i = 10, j = 12;
  
  auto fn = [i, &j] {
   // i is captured by value, so any lookups of i actually turn into
   // a lookup of a member of the lambda object.
   
   // j is captured by reference, so any lookups find j directly.
  };
  
  foo(fn);
}