int main()
{
  const char s1[] = "hello";
  const char s2[] = "world";

  const char *p1[] = { s1, s2 };
  
  decltype(&p1) r1 = &p1;
}