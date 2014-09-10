#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <numeric>
#include <list>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;


vector<string> top100(const vector<string> & input)
{
    unordered_map<string, int> wordsMapToFrequences;
    for (auto i: input)
        wordsMapToFrequences[i] += 1;
        
    multimap<int, const string, greater<int> > mapFrequencesToWords;

    for (const auto & i: wordsMapToFrequences)
    {
        cout << i.first << " " << i.second << " ";
        mapFrequencesToWords.insert(pair<int, string>(i.second, std::move(i.first)));
    }
    
    cout << endl;
        
    for (const auto & i: mapFrequencesToWords)
        cout << i.first << " " << i.second << " ";
        
    cout << endl;

        
    for (const auto & i: wordsMapToFrequences)
        cout << i.first << " " << i.second << " ";
        
    cout << endl;
    
    int counter = 0; vector<string> results;
    for (auto i: mapFrequencesToWords)
    {
        results.push_back(std::move(i.second));
        if (++counter == 100) return results;
    }
    
    return results;
}
 

int main()
{
    /*
    cout << "Hello World" << endl;

    vector<string> v({"aaaa", "aaaa", "aa", "aa", "cat", "dog", "cat", "cat", "cat", "cat", "wolf", "tiger"});
    
    for_each(begin(v), end(v), [] (string &s) { s = "a" + s + "b"; }); 

    vector<string> top100result = top100(v);

    for (auto i: top100result)
        cout << i << " ";
    cout << endl;
    */
    
    
    // my file sort starts here:

    static const int chunkSize = 3;

    vector<int> vector(chunkSize);
    
    ifstream input("input.txt");
    string outputFileName = "output_sorted.txt";
    string tempfileNamePrefx = "temp";

    int tempNumber = 0;
    
    if (!input)
    {
        cout << "Can't open the input file" << endl;
        return 0;
    }
    
    list<pair<unique_ptr<fstream>, string> > tempfiles;
    
    // read chuncks of chunkSize and split into small files with unique names
        
    while (input.good())
    {
        int realSize = 0;
        for_each(begin(vector), end(vector), [&realSize, &input] (int &value) { input >> value; if (!input.good()) return; realSize++; } );
        vector.resize(realSize); // actually realSize is less than chunkSize for last chunk only
        sort(begin(vector), end(vector));
        
        auto filename = tempfileNamePrefx + boost::lexical_cast<string>(tempNumber++);
        auto tempfile = unique_ptr<fstream>(new fstream(filename, fstream::in | fstream::out | fstream::trunc));
        for (auto i: vector)
            (*tempfile) << i << " ";
        
        tempfile->flush();
        tempfiles.push_back(pair<decltype(tempfile), string>(std::move(tempfile), filename));
    }

    // merge files starting with each two small, then double of chunkSize, then double of double ....

    auto listIterPrev = tempfiles.begin(), listIter = ++ tempfiles.begin();
    for(; listIter != tempfiles.end(); ++ ++ listIter, ++ ++ listIterPrev)
    {
        // merge two files and put the result on the tail of the list
        auto & file1 = listIterPrev->first;
        auto & file2 = listIter->first;
        file1->seekg(fstream::beg);
        file2->seekg(fstream::beg);
        
        // create a new file with unique name where merging results are hold
        auto filename = tempfileNamePrefx  + boost::lexical_cast<string>(tempNumber++);
        auto tempfile = unique_ptr<fstream>(new fstream(filename, fstream::in | fstream::out | fstream::trunc));
        int temp;
        (*file1) >> temp;

        bool getFromFirst = false;
        
        // merge two files
        while (true)
        {
            auto & file = getFromFirst ? file1: file2;
            int value;
            // read from a file (first or second)
            (*file) >> value;
            if (!file->good()) { break; }
            if (value <= temp) { (*tempfile) << value << " "; continue; }
            (*tempfile) << temp << " "; 
            temp = value;
            getFromFirst = !getFromFirst; continue;
        }
        
        // write remaider
        (*tempfile) << temp << " ";
        auto & file = file1->good() ? file1: file2;
        while (true)
        {
            int value;
            (*file) >> value;
            if (!file->good()) break;
            (*tempfile) << value << " ";
        }

        tempfiles.push_back(pair<decltype(tempfile), string>(std::move(tempfile), filename));
        file1->close(); remove(listIterPrev->second.c_str());
        file2->close(); remove(listIter->second.c_str()); 
    }

    listIterPrev->first->close();
    rename(listIterPrev->second.c_str(), outputFileName.c_str());

    return 0;
}
    
   