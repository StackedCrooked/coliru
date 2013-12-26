template<typename T>
auto func (T) -> decltype (func (T {}));

template<typename T, typename U>
void foo () {
  func (T{}) + func (U {}) + func (T {} + U {});
}

int
main (int argc, char *argv[])
{
  foo<int,short> ();
}