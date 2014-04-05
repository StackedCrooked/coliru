// regex/regex1.cpp
#include <regex>
#include <iostream>
using namespace std;
void out (bool b)
{
    cout << ( b ? "found" : "not found") << endl;
}

int main()
{
    // ﬁnd XML/HTML-tagged value (using defaultsyntax):
    regex reg1("<.*>.*</.*>");
    bool found = regex_match ("<tag>value</tag>", // data
    reg1); //regular expression
    out(found);
    // ﬁnd XML/HTML-tagged value (tags before and afterthe value must match):
    regex reg2("<\\(.*\\)>.*</\\1>",regex_constants::grep);
    found = regex_match ("<tag>value</tag>", reg2); //regular expression
    out(found);
      
}