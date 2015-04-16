#include <limits>
#include <cstddef>
#include <iostream>
int main()
{  
   std::cout << "INT64_T" << std::endl;
   std::cout << "ACTUAL: " << std::numeric_limits<int64_t>::min() << std::endl;
   std::cout << "RAW: " << -std::numeric_limits<int64_t>::min() << std::endl;
   std::cout << "ABS: " <<  static_cast<uint64_t>(-std::numeric_limits<int64_t>::min())<< std::endl << std::endl; 
   
   std::cout << "INT32_T" << std::endl;
   std::cout << "ACTUAL: " << std::numeric_limits<int32_t>::min() << std::endl;
   std::cout << "RAW: " << static_cast<uint64_t>(-std::numeric_limits<int32_t>::min()) << std::endl;
   std::cout << "ABS: " << static_cast<uint64_t>(-(int64_t)(std::numeric_limits<int32_t>::min())) << std::endl << std::endl; 
   
   std::cout << "INT16_T" << std::endl;
   std::cout << "ACTUAL: " << std::numeric_limits<int16_t>::min() << std::endl;
   std::cout << "RAW: " << static_cast<uint64_t>(-std::numeric_limits<int16_t>::min())  << std::endl;
   std::cout << "ABS: " << static_cast<uint64_t>(-(int64_t)(std::numeric_limits<int16_t>::min())) << std::endl << std::endl; 
   
   
   std::cout << "INT8_T" << std::endl;
   std::cout << "ACTUAL: " << (int64_t)std::numeric_limits<int8_t>::min() << std::endl;
   std::cout << "RAW: " <<  static_cast<uint64_t>(-std::numeric_limits<int8_t>::min()) << std::endl;
   std::cout << "ABS: " <<  static_cast<uint64_t>(-(int64_t)(std::numeric_limits<int8_t>::min())) << std::endl; 
}