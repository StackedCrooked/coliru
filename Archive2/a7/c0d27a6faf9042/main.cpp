#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>


int main()
{
  std::fstream outfile ("new.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  outfile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
  
  try
  {
  char buffer[5];
  strncpy(buffer, "Luigi", 5);
  
  int size = 5;
  // write to outfile
  outfile.write (buffer,size);
  outfile.flush();
  outfile.sync();
  outfile.seekg(0);
  //outfile.close();
  
  char bufferRead[5];
  int sizeRead = 5;
  // read content of file
  outfile.read (bufferRead, sizeRead);
  
  if (outfile)
      std::cout << "all characters read successfully."  << std::endl;
    else
      std::cout << "error: only " << outfile.gcount() << " could be read" << std::endl;
      
  std::cout << "content : " << bufferRead << std::endl;
  
  char bufferRead2[2];
  int sizeRead2 = 2;
  // read content of file
  outfile.read (bufferRead2, sizeRead2);
  std::cout << "content2 : " << bufferRead2 << std::endl;
  
  outfile.close();
  }
  catch(...)
  {
      std::cout << "exception caught" << std::endl;
      outfile.clear();
  }
  outfile.sync();
  
}
