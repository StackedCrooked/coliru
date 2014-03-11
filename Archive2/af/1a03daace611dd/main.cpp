#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <vector>
#include <future>
#include <mutex>
#include <functional>

using namespace std;

std::mutex m;

inline bool match( const std::string &pattern, std::string word )
{
    if ( pattern.size() != word.size() )
        return false;
    for ( size_t i = 0 ; i < pattern.size() ; i++ ) 
        if ( pattern[ i ] != '.' && pattern[ i ] != word[ i ] )
            return false;
    return true;
}

vector<string> find_matches( string pattern, deque<string> &backlog )
{
    vector<string> results;
    for ( ; ; ) {
        m.lock();
        if ( backlog.size() == 0 ) {
            m.unlock();
            return results;
        }
        string word = backlog.front();
        backlog.pop_front();
        m.unlock();
        if ( match( pattern, word ) )
            results.push_back( word );
    }
}

template<class ASYNC>
void print_results( ASYNC &f, string &pattern, int threadno )
{
    vector<string> words = f.get();
    cerr << "Found " << words.size() 
         << " matches for " << pattern 
         << " in thread " << threadno
         << endl;
    for ( auto s : words )
        cout << s << "\n";
}

int main( int argc, char *argv[] )
{
    if ( argc < 2 ) {
        cerr << "Usage: WordSearch match-expression\n\n"
                "match-expression contains lower case letters and periods.\n"
                "The periods will match any character\n";
        return -1;
    }
    string pattern = argv[ 1 ];
    //
    // Load the words into the deque
    //
    ifstream f( "sowpods.txt" );
    if ( !f ) {
        cerr << "Cannot open sowpods.txt in the current directory\n";
        return -1;
    }
    string word;
    deque<string> backlog;
    while ( f >> word )
        backlog.push_back( word );
    //
    // Now process the words and print the results
    //
    auto f1 = async( launch::async, find_matches, pattern, ref(backlog) );
    auto f2 = async( launch::async, find_matches, pattern, ref(backlog) );
    auto f3 = async( launch::async, find_matches, pattern, ref(backlog) );
    print_results( f1, pattern, 1 );
    print_results( f2, pattern, 2 );
    print_results( f3, pattern, 3 );

    return 0;
}
