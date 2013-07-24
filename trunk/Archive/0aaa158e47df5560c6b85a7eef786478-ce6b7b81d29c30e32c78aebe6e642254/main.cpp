#include <map>
#include <string>
#include <iostream>

enum type {Bool, Bool_a, Int_4, Inta_4, Int_8, Inta_8, Float_s, Floata_s, Float_d, Floata_d, Ch_s, Ch_a, Str, Invalid};  

using ret_data =  std::map<std::string, type>;

int main()
{
   ret_data rd;
   rd["bla"] = Int_4; 
   std::cout << rd["bla"] << "==" << Int_4 << "\n";
}