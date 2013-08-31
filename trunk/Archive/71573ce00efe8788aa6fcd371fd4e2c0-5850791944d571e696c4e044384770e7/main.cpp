   #include <chrono>
   #include <iostream>
   int main (int argc, char *argv[]) {
     auto us = std::chrono::microseconds(7);
     std::cout << us << std::endl;  //error
     std::cout << us.count() << std::endl;
   }