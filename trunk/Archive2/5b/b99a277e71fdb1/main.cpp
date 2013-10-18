#include <iostream>
#include <map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <getopt.h>

using namespace std;

int main(int argc, char** argv) {
    
    enum {
        total, unique, individual
    } mode = total;

    for (int c; (c = getopt(argc, argv, "tui")) != -1;) {
        switch (c) {
            case 't': mode = total;
                break;
            case 'u': mode = unique;
                break;
            case 'i': mode = individual;
                break;
        }
    }

    argc -= optind;
    argv += optind;

    using WordIndex = map<string, unsigned>;
    using WordInfo  = WordIndex::value_type;
    WordIndex tally;

    unsigned long total_count = 0;
    for_each(
            istream_iterator<string>(cin), {}, 
            [&] (std::string const& word) mutable { total_count++; tally[word]++; }
        );

    switch (mode) {
        case total: 
            cout << "Total " << total_count << endl;
            break;
        case unique: 
            cout << "Unique " << tally.size() << endl;
            break;
        case individual:
            for (auto const& entry: tally)
                cout << entry.first << "\t" << entry.second << "\n";
            break;
    }
}
