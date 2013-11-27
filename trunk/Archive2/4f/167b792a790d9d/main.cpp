

int main()
{
   volatile int a = 7;
a;   // statement A
volatile int* b = &a;
*b;  // statement B
volatile int& c = a;
c;   // statement C
}