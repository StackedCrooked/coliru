/*
Want to throw an exception that says "failed to do special thingy because of lowlevel socket error blah blah"
*/

#include <system_error>

int main(int argc, char * argv[])
{
   try
   {
      throw std::system_error(EADDRINUSE, std::system_category());
   }
   catch (...)
   {
      std::throw_with_nested(std::runtime_error("failed to bind socket for my special thingy"));
   }
   return 0;
}
