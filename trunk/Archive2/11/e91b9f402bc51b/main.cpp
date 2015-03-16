#include <iostream>
#include <list>
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
    list<pair<char, int>> distances;
    for (char& vowel : vowels)
    {
        distances.push_back(make_pair(vowel, abs(input - vowel)));
    }
    distances.sort(compare);
    pair<char, int> nearest = distances.front();
    if (nearest.second > 0)
    {
        cout << nearest.first;
    }
}