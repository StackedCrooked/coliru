#include <vector>
#include <string>
#include <iostream>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator

int main(int argc, char** argv) {

    for(int i=1; i<argc; ++i) {
      if(std::string("--item") == argv[i] )

        //And remove this item from the list
        argv[i][0] = 0;   //Transform it in an empty string, putting null as first character
      }


for(int i=1; i<argc; ++i)
  std::cout << argv[i] << " ";
}