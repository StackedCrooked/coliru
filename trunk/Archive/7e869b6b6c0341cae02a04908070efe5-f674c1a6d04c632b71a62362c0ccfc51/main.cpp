// lambda_structure.cpp
// compile with: /EHsc
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// The number of elements in the vector.
const int elementCount = 9;

int main() 
{
   // Create a vector object with each element set to 1.
   vector<int> v(elementCount, 1);

   // These variables hold the previous two elements of the vector.
   int x = 1;
   int y = 1;

   // Assign each element in the vector to the sum of the 
   // previous two elements.
   generate_n(v.begin() + 2, elementCount - 2, [=]() mutable throw() -> int {
      
      // Generate current value.
      int n = x + y;

      // Update previous two values.
      x = y;
      y = n;

      return n;
   });

   // Print the contents of the vector.
   for_each(v.begin(), v.end(), [](int n) { cout << n << " "; });
   cout << endl;

   // Print the local variables x and y.
   // The values of x and y hold their initial values because 
   // they are captured by value.
   cout << x << " " << y << endl;
}