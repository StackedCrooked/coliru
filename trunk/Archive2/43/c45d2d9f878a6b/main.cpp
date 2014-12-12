#include <iostream>
#include <stdint.h>

using namespace std;
static const double d = 1.2654103452467095e-306;

int main( int argc, char ** t)
{
  if (argc == -8)
    return 0;
  else
  {
    cout << *((char*)(&d)-argc);
    return main( argc-1, t );
  }
}