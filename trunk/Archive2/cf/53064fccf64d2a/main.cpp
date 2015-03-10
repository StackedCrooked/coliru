#include <string>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>

using namespace std;

boost::regex nameExpression("[a-zA-Z0-9\\s]{1,20}");  // alphanumeric or space and between 1 and 20 characters.
boost::regex nameShortExpression("[a-zA-Z0-9\\s]{1,6}");  // alphanumeric or space and between 1 and 6 characters.

int main () {
  vector<string> strvec;
  strvec.push_back(string("Store 123"));
  strvec.push_back(string("St123"));
  strvec.push_back(string(25,'x'));
  strvec.push_back(string("Store 1.23"));
  
  cout << "Testing Name Value" << endl;
  for (size_t i = 0; i < strvec.size(); i++) {
      std::cout << " > Input string: " << strvec[i] << (boost::regex_match(strvec[i], nameExpression) ? " [valid]" : " [invalid]") << endl;
  }
  
  cout << "Testing NameShort Value" << endl;
  for (size_t i = 0; i < strvec.size(); i++) {
      std::cout << " > Input string: " << strvec[i] << (boost::regex_match(strvec[i], nameShortExpression) ? " [valid]" : " [invalid]") << endl;
  }

  return 0;
}