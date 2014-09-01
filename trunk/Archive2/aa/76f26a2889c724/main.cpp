#include <iostream>
#include <string>
#include <vector>
#include <istream>

using namespace std;

int main()
{
    int n, k, counting;
    cin >> n >>k;
    char trash;
    cin.get(trash);
    vector<string> cards;
    string theline, name;
    cin >> theline;
    cout << theline << "\n";
    for (int i = 0; i < n; i++){
        name = theline[i];
        cards.push_back(name);
    }
    for (int i = 0; i < n; i++){
        if (cards[i] == cards[k-1]){
            counting++;
        }
    }
    int tmp = 0;
    if (cards.size() != k){
        tmp = k - counting;
    }
    counting *= k;
    counting += tmp;
    cout << counting;
    return 0;
}