#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std; 

bool compare(const pair<char, int>& a, const pair<char, int>& b)
{
    return a.second < b.second;
}

int main()
{
    char vowels[] = { 'a', 'e', 'i', 'o', 'u' };
    char input;
    //std::cin >> input;
    input = 'r';
    vector<pair<char, int>> distances;
    for (char& vowel : vowels)
    {
        distances.push_back(make_pair(vowel, abs(input - vowel)));
    }
    sort(distances.begin(), distances.end(), compare);
    pair<char, int> nearest = distances.front();
    if (nearest.second > 0)
    {
        cout << nearest.first;
    }
}