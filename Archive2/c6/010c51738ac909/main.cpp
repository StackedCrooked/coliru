#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <list>
#include <memory>
#include <cstdlib>
#include <boost/lexical_cast.hpp>

using namespace std;

// File Sort based on merge sort
int main(int argc, char ** argv)
{
    cout << "Note: ChunkSize is a parameter, 10 by default" << endl;
    static const int chunkSize = argc < 2 ? 10 : atoi(argv[1]);
    cout << "Current Chunk Size: " << chunkSize << endl;

    ifstream input("input.txt");
    if (!input)
    {
        cout << "Can't open the input file" << endl;
        return 0;
    }

    vector<int> vector(chunkSize);
    string outputFileName = "output_sorted.txt";
    string tempfileNamePrefx = "temp";
    int tempNumber = 0;
    
    list<pair<unique_ptr<fstream>, string> > tempfiles;
    
    // read chuncks of chunkSize and split into small files with unique names
        
    while (input.good())
    {
        int realSize = 0;
        for_each(begin(vector), end(vector), [&realSize, &input] (int &value) { input >> value; if (!input.good()) return; realSize++; } );
        vector.resize(realSize); // actually realSize is less than chunkSize for the last chunk only
        sort(begin(vector), end(vector));
        
        auto filename = tempfileNamePrefx + boost::lexical_cast<string>(tempNumber++);
        auto tempfile = unique_ptr<fstream>(new fstream(filename, fstream::in | fstream::out | fstream::trunc));
        copy(begin(vector), end(vector), ostream_iterator<int>(*tempfile, " "));
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
        merge(istream_iterator<int>(*file1), istream_iterator<int>(), istream_iterator<int>(*file2), istream_iterator<int>(), ostream_iterator<int>(*tempfile, " "));
        tempfiles.push_back(pair<decltype(tempfile), string>(std::move(tempfile), filename));
        file1->close(); remove(listIterPrev->second.c_str());
        file2->close(); remove(listIter->second.c_str());
    }

    listIterPrev->first->close();
    rename(listIterPrev->second.c_str(), outputFileName.c_str());

    return 0;
}
    
   