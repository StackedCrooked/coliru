extern "C++" thread_local int x;

int
main (int argc, char *argv[])
{
  x = 123; // this should result in a linker error
           // x has only been declared, not defined
}