#include <iostream>
#include <boost/lexical_cast.hpp>

int main()
{
   const std::string s1 = "abc",
                     s2 = "123",
                     s3 = "45.6";

   const int   i = boost::lexical_cast<int>(s2);
   std::cout << i << ' ';
   
   const float f = boost::lexical_cast<float>(s3);
   std::cout << f << ' ';
   
   try {
      boost::lexical_cast<int>(s1);  // can't do this!
   }
   catch (boost::bad_lexical_cast&) {
      std::cout << '!' << '\n';
   }
}

// Output: 123 45.6 !