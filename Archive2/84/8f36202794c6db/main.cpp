#include <iostream>

void readFloatData(float *&fBuffer)  //*fBuffer   &fBuffer
{
  // Create New Buffer
  float *fData;
  fData = new float [1000];
  std::cout << static_cast<void*>(fData) << '\n';

  // Pass our buffer Address to user's pointer
  fBuffer = fData;
}

int main ()
{
   float *fMyBuffer;
   
   std::cout << static_cast<void*>(fMyBuffer) << '\n';

   // Pointer Update
   readFloatData ( fMyBuffer ); // &fMyBuffer  *fMyBuffer 
   
   std::cout << static_cast<void*>(fMyBuffer) << '\n';

   // Deallocate Memory
   delete [] fMyBuffer;
}
