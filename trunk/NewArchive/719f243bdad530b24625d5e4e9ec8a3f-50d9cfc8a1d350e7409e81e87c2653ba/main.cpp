int func () {
  throw  1;  
  return 0;
}
 
struct Obj {
  Obj ()
    try : i(func ()) 
  {
    // ... 
  }
  catch (...)
  {
  }
 
  int i;
};
 
int main (int argc, char *argv[])
{
  Obj x;
}