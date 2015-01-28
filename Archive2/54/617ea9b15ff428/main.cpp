#include <iostream>

class A {
private:
  std::string s;
public:
  A() = delete;
  A(const A&) = delete;
  A(A&&) = delete;
  A(const std::string &a) : s(a) {}
};

class Aggr {
private:
  A arr[2];
public:
  Aggr() : arr({"a"}, {"b"}) {}
};