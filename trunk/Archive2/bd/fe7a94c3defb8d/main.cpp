#include <iostream>
#include <string>
#include <vector>

int main()
{
    const char raw[] = "text1\0\0text2\0\0\0text3\0more text";
    std::string clean(std::begin(raw), std::end(raw));
    
    std::vector<std::string> tokens;
    std::string::size_type pos, lastPos = 0;
    while(pos < clean.length())
    {
        // find next delimiter
        pos = clean.find_first_of('\0', lastPos);
        if(pos == std::string::npos) {
            // we've reached the end of the string, so get remaining
            pos = clean.length();
        }
      
        // if not empty add it to the vector
        if(pos != lastPos) tokens.push_back(clean.substr(lastPos, pos - lastPos));
        // increment to next character
        lastPos = pos + 1;
   }
    
    for(auto const& t : tokens) {
        std::cout << '\'' << t << '\'' << std::endl;
    }
}
