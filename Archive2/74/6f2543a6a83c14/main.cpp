#include <unordered_set>
#include <map>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;
using namespace std::placeholders;

struct Shell
{
    int id;
    Shell(const Shell& rhs) : id(rhs.id) { /*cout << "cpy_ctor of " << id << endl;*/ }
    Shell() : id(0) { /*cout << "dflt_ctor of " << id << endl;*/ }
    Shell(int x) : id(x) { /*cout << "ctor of " << id << endl;*/ }
    ~Shell() { /*cout << "dctor " << id << endl;*/ }
    bool operator==(const Shell &other) const { return id == other.id; }
};


struct ShellHash {
    hash<string> m;
    size_t operator() (const Shell &s ) const  {  
        stringstream ss;
        ss << s.id;
        size_t n = m(ss.str());
        return  n;
    }
};

map<size_t, size_t> get_buckets( const unordered_set<Shell, ShellHash> &src )
{
    map<size_t, size_t> stats;
    
    size_t n_buckets = src.bucket_count();
    for( size_t i = 0; i<n_buckets; ++i )
    {
        stats[src.bucket_size(i)] ++;    
    }
    
    return stats;
}

void print_bucket_stats( map<size_t, size_t> stats )
{
    for( auto p : stats ) {
        cout << "<" << p.first << "> = " << p.second << endl;
    }
}

int main()
{
    for(float f = 0.2 ; f < 2.0 ; f+= 0.1)
    {
    unordered_set<Shell, ShellHash> shells;

    shells.max_load_factor(f);

    cout << "FILLING" << endl;

//    size_t n_buckets = shells.bucket_count();
//    cout << "=========> num_buckets = " << n_buckets << endl;

    for(int i=0; i<300000; i++) {
        shells.emplace(Shell(i));
        if( i+3 == shells.bucket_count() ) {
            //cout << "=========> num_buckets = " << shells.bucket_count() << endl;
            //print_bucket_stats(get_buckets(shells));
        }
    }
    cout << "max load factor " << shells.max_load_factor() << endl;
    cout << "load factor " << shells.load_factor() << endl;
    cout << "num_buckets = " << shells.bucket_count() << endl;
    print_bucket_stats(get_buckets(shells));
    }
    
    
    cout << "ACCESSING" << endl;
    
  
    return 0;
}