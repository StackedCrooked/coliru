#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <iterator>
#include <unordered_set>
#include <set>

#include <ctype.h>

using namespace std;
bool isRotation(const std::string& first, const std::string &second)
{
    return ( first + first ).find( second ) != std::string::npos;
}

bool task1(const string& first, const string& second)
{
    if (first.size() != second.size()) return false;
    size_t pos = first.find(*second.begin());
    if (pos == string::npos) return false;
    size_t len = first.size();
    return (first.compare(pos,len-1,second.c_str(),len-pos) == 0 && second.compare(pos,len-1,first.c_str(),len-pos)==0);
}

std::string missingLetter( const std::string& str )
{
    static const std::string alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    std::unordered_set< char > inputs;
    std::transform( str.cbegin(), str.cend(), std::inserter( inputs, inputs.begin() ), [](char ch ) { return toupper(ch); } );
    
    std::string result;
    std::copy_if( alphabet.cbegin(), 
                  alphabet.cend(), 
                  std::back_inserter( result ),
                  [&inputs]( char ch ) { 
                    return inputs.find( ch ) == inputs.cend();
                } );

    return result;
}

std::string  betterMissingLetter( const std::string& str )
{
    static const std::string alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    std::set< char > inputs;
    std::transform( str.cbegin(), str.cend(), std::inserter( inputs, inputs.begin() ), [](char ch ) { return toupper(ch); } );
    
    std::string result;
    std::set_difference( alphabet.cbegin(), alphabet.cend(), 
                         inputs.cbegin(), inputs.cend(), 
                         std::back_inserter( result ) );

    return result;
}

std::string fasterMissingLetter( const std::string& str )
{
    const size_t alphabetSize = 25;
    std::vector< bool > lettersPresense( alphabetSize, false );
    
    std::for_each( str.cbegin(), str.cend(), [&lettersPresense, &str](char ch) { 
            int idx = toupper(ch) - 'A';
            if ( idx >= 0 && idx < str.length() )
            {
                lettersPresense[ idx ] = true;
            }
        });
        
    std::string result;
    for ( size_t i = 0; i <= lettersPresense.size(); ++i )
    {
        if ( !lettersPresense[i] )
        {
            result.push_back( 'A' + i );
        }
    }
    
    return result;
}

void getMisssingLetter(const string& str,string& ret)
{
    static string arr("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    string res;
    for_each(arr.begin(),arr.end(),
             [&](char c) {  bool found = false;
                            for (auto it = str.begin();it !=str.end(); it++)
                                if (c == toupper(*it)) found = true;
                            if (!found) ret.append(1,c);  });
}



void incVector( std::vector< int >& v, int i )
{
    for ( auto& element: v )
    {
        element += i;
    }
}

std::vector< std::string > animate(const std::string& str, int speed)
{
    std::map<char, std::vector<int>> indexes;
    int i = 0;
    for( const auto& ch: str )
    {
        if ( ch != '.' )
            indexes[ch].push_back( i );
        i += 1;
    }
    
    std::vector< std::string > result;
    bool finish = false;
    while ( ! finish )
    {
        std::string particlesState(str.size(), '.');
        bool wasAnyParticlePrinted = false;
        for ( const auto& v : indexes )
        {
            for ( const auto i: v.second )
            {
                if ( i >= 0 && i < str.length() )
                {
                    particlesState[i] = 'X';
                    wasAnyParticlePrinted = true;
                }
            }
        }
        
        finish = !wasAnyParticlePrinted;
        result.push_back( std::move( particlesState ) );
        
        incVector( indexes['R'], speed );
        incVector( indexes['L'], -speed );
        
        
    }
    return result;
}

bool task3(const string& str, vector<string>& res,int vel)
{
    if (vel < 1 || vel > 10) return false;
    if (str.size() > 50 || str.empty()) return false;
    if (!all_of(str.begin(),str.end(),[](char c){ return (c== 'R' || c == 'L' || c == '.'); } ))
        return false;
    vector<char> arrR;
    transform(str.begin(),str.end(), back_inserter(arrR),[](char c){ if (c == 'R') return '1'; return '0'; });
    vector<char> arrL;
    transform(str.begin(),str.end(), back_inserter(arrL),[](char c){ if (c == 'L') return '1'; return '0'; });

    string s1;
    transform(str.begin(),str.end(),back_inserter(s1),[](char c){  if (c == 'R' || c == 'L') return 'X'; return '.'; });
    res.push_back(s1);
    cout << s1 << endl;

    int arrSize = arrR.size();
    //assert(arrR.size() == arrL.size());
    int num = 0;
    do {
        for (int i = arrSize - 1; i >= 0 ; i--) {
            if (i + vel < arrSize)
                swap(arrR[i],arrR[i+vel]);
            else
                arrR[i] = '0';
        }
        for (int i = 0; i < arrSize; i++) {
            if (i - vel >= 0)
                swap(arrL[i],arrL[i-vel]);
            else
                arrL[i] = '0';
        }
        num = 0;
        string sres;
        for (int i = 0; i < arrSize; ++i) {
            if (arrR[i] == '1' || arrL[i] == '1') {
                sres.append(1,'X');
                num++;
            }
            else
                sres.append(1,'.');
        }
        res.push_back(sres);
        cout << sres << endl;
    } while(num > 0);
    return true;
}

int main()
{
    cout << "========= task 1 ===========" << endl;
    string s1("hewloworld");
    string s2("worldhewlo");
    cout << (task1(s1,s2) ? "Yes" : "No") << endl;
    std::cout << (isRotation(s1, s2) ? "Yes" : "No") << std::endl;
    

    cout << "========= task 2 ===========" << endl;
    string sentence("Abc db g fac");
    string result;
    getMisssingLetter(sentence,result);
    cout << result << endl;
    std::cout << missingLetter( sentence ) << endl;
    std::cout << betterMissingLetter( sentence ) << endl;
    std::cout << fasterMissingLetter( sentence ) << endl;
    cout << "========= task 3 ===========" << endl;
    vector<string> res3;
    task3("LRRL.LR.LRR.R.LRRL.",res3,1);
    auto task3 = animate("LRRL.LR.LRR.R.LRRL.", 1);
    std::copy(task3.cbegin(), task3.cend(), std::ostream_iterator< std::string >( std::cout, "\n") );
    return 0;
}