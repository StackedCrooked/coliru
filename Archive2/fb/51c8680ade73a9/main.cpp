#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main() {
    map<string,vector<int> > misspelled;
    
    auto add = [&misspelled](const std::string &word, const int lineNum) {
        misspelled[word].push_back(lineNum); 
    };
    
    add("debugging", 1);
    add("process", 2);
    add("removing", 2);
    add("programming", 3);
    add("process", 4);
    add("putting", 4);           

    for (map<string, vector<int>>::iterator i = misspelled.begin(); i != misspelled.end(); i++)
    {
        cout << i->first << ": ";
        for (vector<int>::iterator j = i->second.begin(); j != i->second.end(); j++)
        {
            cout << *j << endl;
        }
    }
}