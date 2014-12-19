cat<<INPUT > input.txt; clang++ -std=c++11 -Os -Wall -pthread main.cpp && time ./a.out
object: Foo
  name: Joe Bloggs
  age: 26
object: Foo
  age: 42
  name: Douglas Adams
object: Foo
  name: Lego Man
object: Bar
  location: UK
INPUT