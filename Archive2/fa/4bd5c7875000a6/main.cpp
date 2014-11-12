#include <iostream>
#include <sstream>
#include <locale>

class num_get : public std::num_get<char>
{
public:
    // Override do_get which is a virtual function in the std::num_get<char>
    // base class. It is called by the public member function get() in the
    // implementation of std::basic_istream<charT>::operator>>(int&)

    // You might want to put this into a helper function and call it in
    // both the signed and unsigned overloads

    iter_type do_get( iter_type it, iter_type end, std::ios_base& str,
                      std::ios_base::iostate& err, long& v ) const
    {
        // Store a locale object for later use.
        std::locale loc(str.getloc());

        // delegate the extraction to the default base class function
        it = std::num_get<char>::do_get(it, end, str, err, v);
        
        // If the extraction succeeded, tell the user if positive or negative,
        // or zero
        if (!(err & std::ios_base::failbit))
        {
            if (v == 0)
                std::cout << "The number you entered is a zero.\n";
            std::cout << "You entered a " <<
                ((v >= 0) ? "positive" : "negative") << " number.\n";
                    
            // Check whether the end has not been met (because of further
            // input that can't be used in a long). And if the first character
            // of that input is a decimal point (or '.' in en_US) then get
            // rid of that input for convenience, and set failbit

            if (it != end && *it == std::use_facet<std::numpunct<char>>(loc).decimal_point())
            {
                // We get rid of that input by calling the base class function
                // again which does all the necessary parsing.

                // Note that if you do not want to get rid of the invalid
                // floating point input, then simply remove these two lines.
                it = std::num_get<char>::do_get(++it, end, str, err, v);
                // Clear out v
                v = 0;
                
                // set failbit
                err |= std::ios_base::failbit;
            }
        }    
        return it;
    }
};
    
int main()
{
    std::stringstream ss;
    std::locale new_locale(ss.getloc(), new num_get);
    ss.imbue(new_locale);
    
    ss.str("123");
    int n;
    
    if (ss >> n) std::cout << "#1 Works\n"; else std::cout << "Error!\n";
    
    ss.clear();
    ss.str("123.456");
    
    if (ss >> n) std::cout << "#2 Works\n"; else std::cout  << "Error!\n";
}