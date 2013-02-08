#include <boost/algorithm/string/replace.hpp>
#include <iostream>
#include <string>


struct Encoder
{
    Encoder(const std::string & inDelimiter, const std::string & inEscape) :
        mDelimiter(inDelimiter),
        mEscape(inEscape),
        mMetaEscape(inEscape + inEscape)
    {
    }

    void encode(std::string & text) const
    {
        using boost::algorithm::replace_all;
        replace_all(text, mEscape,    mMetaEscape);
        replace_all(text, mDelimiter, mEscape + mDelimiter);
    }

    void decode(std::string & text) const
    {
        using boost::algorithm::replace_all;
        replace_all(text, mEscape + mDelimiter, mDelimiter);
        replace_all(text, mMetaEscape, mEscape);
    }

    std::string mDelimiter, mEscape, mMetaEscape;
};

int main()
{
    Encoder enc(",", ".");
    
    std::string msg = "a,b.d";
    std::cout << "Original: " << msg << std::endl;
    
    enc.encode(msg);
    std::cout << "Encoded: " << msg << std::endl;
    
    enc.decode(msg);
    std::cout << "Decoded: " << msg << std::endl;
}
