#include <string>
#include <ios>
#include <type_traits>
#include <cstdlib>
#include <fstream>
#include <iostream>

int main() 
{
    
    //std::cout <<"boooo";
    
    //printf();
    
    //system("echo 3324234 > damp");
    //system("pwd > damp");
    system("echo '#! /bin/sh' > damp");
    system("echo 'echo Wow are you sure this is secure' >> damp");
    system("echo '' >> damp");
    system("chmod 755 damp");
    system("./damp > damp2");
    
    
    std::ifstream ifile("damp2");
    
    if (ifile.is_open())
  {
      std::string line;
    while ( getline (ifile,line) )
    {
      std::cout << line << '\n';
    }
    ifile.close();
  }
    //std::cout << ifile;
 
}