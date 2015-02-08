#include <iostream>
#include <regex>

using namespace std;

void testMatch( const std::regex &ex, const string st )
{
    cout << "Matching " << st << endl;
    if ( std::regex_match( st, ex ) )
        {
            cout << " matches" << endl;
        }
    else
        {
            cout << " doesn't match" << endl;
        }
}

void testSearch( const std::regex &ex, const string st )
{
    cout << "Searching " << st << endl;
    string::const_iterator start, end;
    start = st.begin();
    end = st.end();
    std::match_results<std::string::const_iterator> what;
    std::regex_constants::match_flag_type flags = std::regex_constants::match_default; // ****
    while( std::regex_search( start, end, what, ex, flags ) )
        {
            cout << " " << what.str() << endl;
            start = what[0].second;
        }
}

int main()
{
    static const std::regex ex( "[Rr]eg...r" );
    testMatch( ex, "regular" );
    testMatch( ex, "abc" );
    testMatch( ex, "some regular expressions are Regxyzr" );
    testMatch( ex, "RegULarexpressionstring" );
    testSearch( ex, "regular" );
    testSearch( ex, "abc" );
    testSearch( ex, "some regular expressions are Regxyzr" );
    testSearch( ex, "RegULarexpressionstring" );
    return 0;
}
