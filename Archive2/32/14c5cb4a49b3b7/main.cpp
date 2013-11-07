#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <map>

using namespace std;

map<size_t, size_t> get_stats( const unordered_set<int>& s )
{
    map<size_t, size_t> stat;
    for( size_t i = 0; i<s.bucket_count(); ++i )
    {
        stat[i] += s.bucket_size(i);
    }
    return stat;
}

void print_stats( unordered_set<int> &m )
{
    printf("%5ld: ", m.size());
    double sz = m.size();
    const map<size_t, size_t> stats = get_stats(m);
    for( auto p : stats ) {
        double perc = p.second / sz;
        printf("[%ld] %3.2f%% ", p.first, 100*perc);
    }
    printf("\n");
}

int main()
{
    unordered_set<int> m;
    for(int i=0; i<100000; i++) {
        m.insert(rand());
        if ( (i % 500)==0 )
            print_stats(m);
    }
}


