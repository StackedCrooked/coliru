int main()
{
  const char s1[] = "hello";
  const char s2[] = "world";

  const char *p1[] = { s1, s2 };
  const char **p2 = p1;
  
  const char ***r1 = &p2;
}