typedef void (*fn_t)();
void fn() { }

fn_t pFn = fn;

fn_t& distinguish(fn_t pFn)
{
  return pFn;
}

int main()
{
  // call the one that takes a parameter from which I cannot get the address of the function pointer
  distinguish(fn);

  fn_t pFn = fn;
// call the one that takes a parameter from which I can get the address of the function pointer
  distinguish(pFn);
  distinguish(pFn); // this will work
  distinguish(fn); // this will not work
  return 0;
}