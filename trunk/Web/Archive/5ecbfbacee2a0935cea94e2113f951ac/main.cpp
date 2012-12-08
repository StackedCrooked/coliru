#include <iostream>
#include <string>


void searchAndReplace(std::string& value, std::string const& search,std::string const& replace);
std::string enc(const std::string & s);
std::string dec(std::string s);


int main()
{
    const std::string orig = "abc\tdef";
    std::cout << "Orig: " << orig << std::endl;
    std::cout << "Enc: " << enc(orig) << std::endl;
    std::cout << "Dec: " << dec(enc(orig)) << std::endl;
}


std::string enc(const std::string & s)
{
    std::string result;
    result.reserve(2 * s.size());
    for (auto c : s)
    {
        if (c == '\t')
        {
            result.push_back('\\');
            result.push_back('t');
        }
        else
        {
            result.push_back(c);
        }
    }
    return result;
}


std::string dec(std::string s)
{
    searchAndReplace(s, "\\t", "\t");
    return s;
}

void searchAndReplace(std::string& value, std::string const& search,std::string const& replace)
{
    std::string::size_type  next;

    for(next = value.find(search);        // Try and find the first match
        next != std::string::npos;        // next is npos if nothing was found
        next = value.find(search,next)    // search for the next match starting after
                                          // the last match that was found.
       )
    {
        // Inside the loop. So we found a match.
        value.replace(next,search.length(),replace);   // Do the replacement.
        next += replace.length();                      // Move to just after the replace
                                                       // This is the point were we start
                                                       // the next search from. 
    }
}