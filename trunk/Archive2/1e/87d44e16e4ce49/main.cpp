
    #include <string>
    #include <iostream>
    #include <regex> // NFG
   
    int main (void)
    {
    std::string text ("here is a string of letters");
    std::regex pattern ("e");
    std::string replacement ("E");
    std::string replaced;

    replaced = std::regex_replace (text, pattern, replacement);
    std::cout << "replaced = \"" << replaced << "\"" << std::regex_replace (text, pattern, replacement) << std::endl;



    return 0;
    }
