#include <string>
#include <iostream>
#include <algorithm>

int main() {
    using namespace std;
    string d_26 = "2014_12_26";
    string d_27 = "2014_12_27";
    string d_25 = "2014_12_25";
    string y1_25 = "1914_12_26";
    string y2_25 = "2015_12_26";


   std::cout << "2014_12_25 < 2014_12_26: " << (d_25 < d_27) << "..." << std::endl;
   std::cout << "2014_12_26 < 2014_12_27: " << (d_26 < d_27) << "..." << std::endl;

   std::cout << "1914_12_26 < 2014_12_25: " << (y1_25 < d_25) << "..." << std::endl;
   std::cout << "(y1_25 < d_25), (d_25  < d_26), (d_26 < y2_25): " 
                                                 << (y1_25 < d_25) << ", " 
                                                << (d_25  < d_26) << ", " 
                                                << (d_26 < y2_25) << "..." << std::endl;





}