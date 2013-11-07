#include <iostream>
#include <string>
#include <vector>

#include <ctime>

using namespace std;

int main()
{
    const time_t now = time(0);
    cout << now << "\n";
    struct tm date = *localtime(&now);
    date.tm_hour = 0;
    date.tm_min  = 0;
    date.tm_sec  = 0;
    date.tm_isdst = -1;
    vector<char> dateResult(11);
    cout << dateResult.size() << "\n";
    for (vector<char>::iterator it = dateResult.begin(); it != dateResult.end(); ++it)
        cout << "a";
    cout << "\n";
    
    date.tm_mday = 0;
    time_t lastDayOfMonth = mktime(&date);
    date = *localtime(&lastDayOfMonth);
    strftime(&dateResult[0], dateResult.size(), "%d/%m/%Y", &date);
    string dateResultString(dateResult.begin(), dateResult.end());
    cout << dateResultString << "\n";
    
    date.tm_mday = 0;
    lastDayOfMonth = mktime(&date);
    date = *localtime(&lastDayOfMonth);
    strftime(&dateResult[0], dateResult.size(), "%d/%m/%Y", &date);
    dateResultString.assign(dateResult.begin(), dateResult.end());
    cout << dateResultString << "\n";
}
