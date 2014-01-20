// Everything in this block has C linkage
extern "C" {

   // Declaration of g_myVal
   extern int g_myVal;

   // Definition of g_myVal2
   int g_myVal2;
}

int main()
{
    g_myVal2 = 5;  // ok
    g_myVal  = 6;  // not okay - linker error, symbol not found
}