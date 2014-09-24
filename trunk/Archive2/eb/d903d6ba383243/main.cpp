// basic file operations
#include <iostream>
#include <fstream>

int main () {
  std::ofstream htmlfile;
  htmlfile.open ("index.html");
  htmlfile << "<html>";
  htmlfile << "</html>";
  htmlfile.close();
}