// ios::exceptions
#include <iostream>     // std::cerr
#include <fstream>      // std::ifstream

int main () {
  std::ifstream file;
  file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
  try {
    file.open ("test.txt");
    while (!file.eof()) file.get();
    file.close();
  }
  catch (const std::exception& e) {
    std::cerr << "Exception opening/reading/closing file\n: e.what(): " << e.what();
  }

  
//  catch (std::ifstream::failure e) {
//    std::cerr << "Exception opening/reading/closing file\n: e.what(): " << e.what();
//   ---> this would give:  e.what(): basic_ios::clear() 
//  }

  return 0;
}