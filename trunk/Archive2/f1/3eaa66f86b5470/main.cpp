#include <string>
#include <fstream>
#include <iostream>

int main(){
  std::string nomSite;

  std::cout << "Sur quel site etes-vous inscrit?" << std::endl;
  std::cin >> nomSite;

  std::string const path_base = "C:\\Users\\Public\\Documents\\donneesMemoirePass\\";

  std::ofstream compte(path_base + nomSite + ".txt");
}