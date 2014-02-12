int func()
{
  return 0;
}

int func2(void)
{
  return 1;
}

int main(void)
{
  int a;

  a = func(a, a); /* A */
  a = func2(a);   /* B */

  return 0;
}