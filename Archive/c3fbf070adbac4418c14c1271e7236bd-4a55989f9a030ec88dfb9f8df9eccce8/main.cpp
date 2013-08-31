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

string header() {
    return string("<!DOCTYPE html>\n<html>\n\t<body>\n");
}

string footer() {
    return string("\t</body>\n</html>\n");
}

string addTag(string tag) {
    return string("\t\t") + makeTag(tag) + string("\n");
}

string makeHTMLDocument(vector<string> tags) {
  string result = string("") + header();
  
  for(int i = 0; i < tags.size(); i++)
        result += addTag(tags[i]);
  
  return result + footer();
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
