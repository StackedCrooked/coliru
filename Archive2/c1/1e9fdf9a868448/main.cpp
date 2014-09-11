#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
   string dbond = "FixingMethod    \"RATESET\" CreditName    \"SPAIN_EUR\" GuarantorName	\"\" BondCode\"\"";
   auto reg = std::regex("CreditName[\\s]+[\\S]+");
   auto result = regex_replace(dbond, reg, "CreditName\\t\"\"");
   cout << result << endl; 
   return 0;
}
