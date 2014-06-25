#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

template <class T>                                      // const or not
vector<T> markov_walk( map<T, map<T,unsigned long long>> chain ) {
    vector<T> result;

    T state = "";
    do {
        // get total 'strength' of links
        unsigned long long total = 0;
        for( auto &i : chain.at(state) ) {
            total += i.second;
        }

        // gen a random number between 0 and total strength
        unsigned long long r = rand() % total; // XXX fix this rand()

        // select next state
        for( auto &i : chain.at(state) ) {
            if( r - i.second > r ) { // check for underflow
                result.push_back(i.first);
                state = i.first;

                cout << "found new state!: " << state << endl;
                break;
            } else {
                r -= i.second;
            }
        }
        
        cout << "Did we find a new state?" << endl;
    } while( state != "" );

    return result;
}

template <class T>
basic_string<T> rand_name( map<basic_string<T>, map<basic_string<T>,unsigned long long>> chain ) {
    basic_ostringstream<T> oss;

    vector<basic_string<T>> vec = markov_walk( chain );

    for( auto &i : vec ) {
        oss << i;
    }

    return oss.str();
}

map<string, map<string,unsigned long long>> make_markov( vector<string> list ) {
    map<string, map<string,unsigned long long>> chain;

    for( auto &entry : list ) {
        string last = "";
        for( auto &i : entry ) {
            string s; s += i;
            if( chain[last].find(s) == chain[last].end() )
                chain[last][s] = 0;

            chain[last][s]++;
            
            last = i;
        }
        
        if( chain[last].find("") == chain[last].end() )
            chain[last][""] = 0;

        chain[last][""]++;
    }

    return chain;
}


int main() {
    srand( time(NULL) );
    vector<string> list = {
        "xunie",
        "alex"
    };

    map<string, map<string,unsigned long long>> chain = make_markov( list );

    for( unsigned int i = 0; i < 10; i++ ) {
        cout << rand_name(chain) << endl;
    }

    return 0;
}