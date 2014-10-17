#include <sstream>
#include <iostream>

int main()
{
   std::istringstream strm;
   char arr[] = "1234567890";

   strm.rdbuf()->pubsetbuf(arr, sizeof(arr));
   int i;
   strm >> i;
   std::cout << i; 
}
