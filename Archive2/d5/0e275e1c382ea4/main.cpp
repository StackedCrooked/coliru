#include <iostream>
#include <vector>

using namespace std;

class BS/*: public Atomic*/{

public:

    static const unsigned int numberOfFiles = 10;
    static const unsigned int minFileSize = 5;
    static const unsigned int maxFileSize = 15;


   // A static member function to initialize the static member variable
   static vector<unsigned int> initFileSizes(const unsigned int numOfFiles, const     unsigned int min, const unsigned int max);


   static vector<unsigned int> fileSizes; // Static member variable I am having problem
};


// initializing the static member variable
vector<unsigned int> BS::fileSizes = BS::initFileSizes(BS::numberOfFiles,  BS::minFileSize, BS::maxFileSize);

#include <stdlib.h>

// static member function definition
vector<unsigned int> BS::initFileSizes( const unsigned int numOfFiles, const unsigned int min, const unsigned int max)
{
  vector<unsigned int> sizes;
  for(int i=0; i<numOfFiles; ++i) sizes.push_back((min + rand()%max));

  return sizes;
}

int main()
{}
