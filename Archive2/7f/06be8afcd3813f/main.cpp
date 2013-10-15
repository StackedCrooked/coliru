#include <iostream>
#include <string>
#include <time.h>
#include <set>
#include <utility>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

using namespace std;

bool stringMatchWithWildcards (const std::string str, const std::string strWithWildcards)
{
    const std::string wildcard="*";

    const bool startWithWildcard=(strWithWildcards.find(wildcard)==0);
    int pos=strWithWildcards.rfind(wildcard);
    const bool endWithWildcard = (pos!=std::string::npos) && (pos+wildcard.size()==strWithWildcards.size());

    // Basically, the point is to split the string with wildcards in strings with no wildcard.
    // Then search in the first string for the different chunks of the second in the correct order
    std::vector<std::string> vectStr;
    boost::split(vectStr, strWithWildcards, boost::is_any_of(wildcard));
    // I expected all the chunks in vectStr to be non-empty. It doesn't seem the be the case so let's remove them.
    vectStr.erase(std::remove_if(vectStr.begin(), vectStr.end(), std::mem_fun_ref(&std::string::empty)), vectStr.end());

    // Check if at least one element (to have first and last element)
    if (vectStr.empty())
    {
        return (startWithWildcard || endWithWildcard || str.empty());
    }

    // First Element
    std::vector<std::string>::const_iterator vectStrIt = vectStr.begin();
    std::string aStr=*vectStrIt;
    cout << "first " << str.find(aStr, 0) << endl;
    if (!startWithWildcard && str.find(aStr, 0)!=0) {
        cout << "first element stuff" << endl;
        return false;
    }

    // "Normal" Elements
    bool found(true);
    pos=0;
    std::vector<std::string>::const_iterator vectStrEnd = vectStr.end();
    for ( ; vectStrIt!=vectStrEnd ; vectStrIt++)
    {
        aStr=*vectStrIt;
        cout << aStr << endl;
        cout << "pos "<< pos << endl;
        pos=str.find(aStr, pos);
        if (pos==std::string::npos)
        {
            cout << "normal" << endl;
            return false;
        }
        pos+=aStr.size();
    }

    // Last Element
    cout << "1 " << str.rfind(aStr) << endl;
    cout << "2 " << aStr.size() << endl;
    cout << "3 " << str.size() << endl;
    return (endWithWildcard || str.rfind(aStr)+aStr.size()==str.size());
}

int main()
{
    string iString = "ABC*ABC";
    string iCommaSeparatedList = "Y";
    string loopString = "ABC";
    
    if (stringMatchWithWildcards(iString, loopString))
    {
        cout << "isStringInTheCommaSeparatedList : String '" << iString << "' found in the list '" << iCommaSeparatedList << "' (in " << loopString << ")";
        return true;
    }


} 