#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

typedef map<string, size_t> Concordance;

ostream& operator << (ostream& out_s, Concordance const& c)
{
    out_s << "Word" << setw(10) << " " << "Count" << endl;
    out_s << "--------------------" << endl;
    for(auto const& entry : c)
        out_s << entry.first << setw(10) << " " << entry.second << endl;
    return out_s << "--------------------" << endl;
}

Concordance build_list(ifstream& in_file)
{
    Concordance c;

    string word;
    while(in_file >> word)
        c[word]++;

    return c;
}

int main()
{
    cout << "Enter a file name: ";
    string file_name;
    getline(cin, file_name);
    if (!cin)
        return 255;

    ifstream in_file(file_name);
    if (!in_file)
        return 254;

    auto concordance = build_list(in_file);
    cout << concordance;
}   

