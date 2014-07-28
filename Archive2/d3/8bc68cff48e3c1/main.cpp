#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

struct Person {};

int main() {
    using namespace std;
    using stVecPair = pair<const string, vector<Person *>>;
    
    const map<string, vector<Person *>> m_teams;
    set<string> teamNames;
    
    transform(m_teams.begin(), m_teams.end(), inserter(teamNames, teamNames.end()),
    [](stVecPair team) -> string { return team.first; });   
}