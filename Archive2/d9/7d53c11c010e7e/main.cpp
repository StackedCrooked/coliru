#include <regex>
#include <iostream>

int main()
{
    using namespace std;
    
    regex partialCommReg(R"((^[\/][\*][\S\s]*$))");
    if (regex_match ("/* ", partialCommReg) )
      cout<<"ok";
}
