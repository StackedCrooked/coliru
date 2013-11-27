int main()
{
  char a[8]{};
  int x = *reinterpret_cast<int*>(a);
  char* p = a;
  int y = *reinterpret_cast<int*>(p);
  return x+y;
}