template<typename T, typename = decltype (T::deleted, int { })>
int func (int);

template<typename T>
char func (...);

struct Obj {
  void deleted () = delete;
};

int
main (int argc, char *argv[])
{
  decltype (func<Obj> (0)) foo;
  (void)foo;
}
