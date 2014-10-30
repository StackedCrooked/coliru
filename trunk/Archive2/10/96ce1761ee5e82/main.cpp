#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
#include <map>
#include <vector>

using namespace std;

int main()
{
    string text = "A quick brown fox is actually brown, wow!";
	map<string, int> entries;

	regex reWhitespaces("\\W+");
	for (auto it = sregex_token_iterator(text.begin(), text.end(), reWhitespaces, -1); it != sregex_token_iterator(); ++it)
		++entries[*it];

	typedef pair<string, int> EntryPair;
	struct ReverseEntryPairComparator{
		bool operator()(const EntryPair &l, const EntryPair &r) const {
			return make_pair(l.second, l.first) < make_pair(r.second, r.first);
		}
	};
	cout << max_element(entries.begin(), entries.end(), ReverseEntryPairComparator())->first << endl;
}
