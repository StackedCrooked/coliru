int main(int argc, char* argv[])
{
  struct
  {
    int a;
    int b;
  } c;

  c.a = atoi(argv[1]);
  c.b = atoi(argv[2]);
  __stosb((unsigned char*)&c, 0, sizeof(c));
  printf("%u %u\n", c.a, c.b);
}