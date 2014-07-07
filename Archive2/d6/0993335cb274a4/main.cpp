#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    std::vector<std::string> myvector{"", "1", "", "2", "", "", "3", ""};
    
    for (vector<std::string>::iterator i=myvector.begin(); 
              i != myvector.end(); /* do nothing here */) {
       if (*i == "") {
          i = myvector.erase(i);
       } else {
         ++i;
       }
    }
    
    for (const auto &s : myvector) {
        std::cout << s << ' ';   
    }
}