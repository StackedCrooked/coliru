#include <iostream>
#include <numeric>
using namespace std;

int tier1();

int main(void) {
    return tier1();
}

static int getnumber(std::string prompt) {
    if (!std::cin)
        return 0;

    int i;
    std::cout << prompt;
    std::cin >> i;

    while(!std::cin) {
        if (std::cin.eof()) {
            exit(1); 
        }
        std::cin.clear();
        std::cin.ignore(1<<30, '\n');
        std::cout << prompt;
        std::cin >> i;
    }

    return i;
}

#include <map>
#include <algorithm>

int tier1() {
    using namespace std;
    using county = int;

    static constexpr int number_of_counties   = 4;
    static constexpr int number_of_candidates = 2;
    
    map<county, size_t[number_of_candidates]> votes;

    for (int cty = 0; cty < number_of_counties; cty++) {
        for (int cand = 0; cand < number_of_candidates; cand++) {
            votes[cty][cand] = getnumber("How many votes did the candidate " + to_string(cand) + " get in county " + to_string(cty) + "? ");
        }
        if (std::accumulate(begin(votes[cty]), end(votes[cty]), 0u) > 100)
            cout << "County has too many votes. Exiting!\n"; // Print an error
    }

    size_t totals[number_of_candidates] = { 0 };

    for(auto& cty: votes) {
        for (auto in = begin(cty.second), accum = begin(totals); accum < end(totals);) {
            *accum++ += *in++;
        }
    }

    auto winner = max_element(begin(totals), end(totals));

    cout << "The winner of the election is candidate " << distance(totals, winner) << "\n";
    
    cout << "Here is the voting results:\n";
    for (int cand = 0; cand < number_of_candidates; cand++) {
        cout << "candidate " << cand << " got " << totals[cand] << " votes\n";
    }

    return 0;
}
