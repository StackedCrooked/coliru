#include <boost/circular_buffer.hpp>
#include <iostream>

int main()
{
   auto print = [](const boost::circular_buffer<int>& b)
   {
      std::cout << "buffer" << std::endl;
      for (auto p : b) { std::cout << p << std::endl; };
   };

   boost::circular_buffer<int> buffer(3);
   buffer.push_back(1);
   buffer.push_back(2);
   buffer.push_back(3);
   print(buffer);
   buffer.push_back(4);
   print(buffer);
}