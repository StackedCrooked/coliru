#include <string>
using namespace std;

constexpr static size_t NUM_EXAMS = 4;

struct student {
    string last_name;
    string first_name;
    double exams[NUM_EXAMS];
    double average;
    char   letter_grade;
    bool   passed;

    bool operator<(student const& o) const { return last_name < o.last_name; }
};

#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>

int main() {
    student ss[] = {
        {    "Jones",       "John", {  87,  66,  92,  88 }, 83.25, 'B',  true },
        {    "Smith",      "Peter", {  55,  66,  63,  58 },  60.5, 'D',  true },
        {    "Quest",     "Nicole", {  79,  89,  99,  98 }, 91.25, 'A',  true },
        {       "Wu",         "Li", {  98,  99, 100,  91 },    97, 'A',  true },
        {     "West",    "Vincent", {  80,  80,  88,  89 }, 84.25, 'B',  true },
        { "McCartin",      "Susan", {  80,  90, 100,  85 }, 88.75, 'B',  true },
        { "Ibrahima",    "Shuhuru", {  45,  65,  54,  60 },    56, 'F', false },
        {    "Burns", "Antoinette", {  90,  90,  90,  90 },    90, 'A',  true },
        {       "Ng",   "Lawrence", { 100, 100,  90,  76 },  91.5, 'A',  true },
        {  "Ziggler",     "Bertha", {  65,  55,  58,  58 },    59, 'F', false },
        {  "Ionella",       "Jean", { 100, 100, 100, 100 },   100, 'A',  true },
        {   "Vogler",     "Samuel", {  40,  50,  60,  70 },    55, 'F', false },
        {    "Perry",        "Jim", {  67,  87,  76,  54 },    71, 'C',  true },
    };

    std::sort(begin(ss), end(ss));

    for(auto& s : ss)
        cout << 
            setw(12) << right << s.first_name   << 
            setw(12) << right << s.last_name    << 
            setw(4)  << right << s.exams[0]     << 
            setw(4)  << right << s.exams[1]     << 
            setw(4)  << right << s.exams[2]     << 
            setw(4)  << right << s.exams[3]     << 
            setw(8)  << right << s.average      << 
            setw(2)  << right << s.letter_grade << 
            " " << (s.passed?"Pass":"Fail") << "\n";

    cout << " ----------------------------------------\n";

    std::sort(begin(ss), end(ss), [](student const& a, student const& b){return b<a;});

    for(auto& s : ss)
        cout << 
            setw(12) << right << s.first_name   << 
            setw(12) << right << s.last_name    << 
            setw(4)  << right << s.exams[0]     << 
            setw(4)  << right << s.exams[1]     << 
            setw(4)  << right << s.exams[2]     << 
            setw(4)  << right << s.exams[3]     << 
            setw(8)  << right << s.average      << 
            setw(2)  << right << s.letter_grade << 
            " " << (s.passed?"Pass":"Fail") << "\n";
}
