int main()
{
double pie = 3.14159;
int myVal{3.1415};

myVal = int(pie); // type conversion using operator()
myVal = int{pie}; // uniform initialization syntax
}