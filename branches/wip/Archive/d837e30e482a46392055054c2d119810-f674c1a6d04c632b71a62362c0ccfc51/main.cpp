#include <iostream>
#include <string>


inline std::string BufferToStr(const unsigned char* buffer, int index, size_t length)
{
   std::string retValue(reinterpret_cast<const char*>(&buffer[index], length));
   return retValue;
}


int main()
{
    
}
