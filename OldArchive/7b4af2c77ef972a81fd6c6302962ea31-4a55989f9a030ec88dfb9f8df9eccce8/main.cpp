#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

string makeTag(string tag) {
    return string("<") + tag + string("></") + tag + string(">");
}

string makeHTMLDocument(vector<string> tags) {
  string result = string("<!DOCTYPE html>\n<html>\n\t<body>\n");
  
  for(int i = 0; i < tags.size(); i++)
        result += string("\t\t") + makeTag(tags[i]) + string("\n");

  return result + string("\t</body>\n</html>\n");
}



int main(int argc, char **argv)
{
    vector<string> *arguments = new vector<string>();
    
    for(int i = 1; i < argc; i++)
    {
        arguments->push_back(string(argv[i]));
    }
    
    cout << makeHTMLDocument(*arguments);
    
    return 0;
}
