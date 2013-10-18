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

    for_each(
            istream_iterator<string>(cin), {}, 
            [&tally] (std::string const& word) mutable { tally[word]++; }
        );

    switch (mode) {
        case total: 
            {
                auto total = std::accumulate(begin(tally), end(tally), 0u, [](unsigned accum, WordInfo const& el) { return accum + el.second; });
                cout << "Total " << total << endl;
            }
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
