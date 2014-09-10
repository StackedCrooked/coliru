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
#include <climits>


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

void Show(int&& i)
{
    i = 50;
    cout << "int&& called" << endl;
}
 
void Show(int& i)
{
   i = 50;
   cout << "int& called " << i << endl;
}
 
template<typename T> void Foo(T&& x)
{
    cout << "straight: ";
//    Show(x);
//    cout << x << " " << endl;
 
//    cout << "move: ";
    Show(move(x));
     
    cout << "forward: ";
 //   Show(forward<T>(x));
     
    cout << endl;
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
    
    Foo(10);
 
    int x=10;
    Foo(x);
    cout << x << " " << endl;

    vector<int> u(10);
    iota(begin(u), end(u), 0);
    shuffle(begin(u), end(u), default_random_engine(time(0) % 100));
    for (auto i: u) cout << i << " ";
    cout << endl;
    */
    
    static const int buket_size = 3;

    vector<int> vector(buket_size);
    
    ifstream input("input.txt");
    string output_file_name = "output_sorted.txt";

    string temp_name = "temp";
    int temp_number = 0;
    
    if (!input)
    {
        cout << "Can't open the input file" << endl;
        return 0;
    }
    
    list<pair<unique_ptr<fstream>, string> > tempfiles;
    
    // read and split into small files
        
    while (input.good())
    {
        int real_size = 0;
        for_each(begin(vector), end(vector), [&real_size, &input] (int &value) { input >> value; if (!input.good()) return; real_size++; } );
        vector.resize(real_size);
        sort(begin(vector), end(vector));
        
        auto filename = temp_name + boost::lexical_cast<string>(temp_number++);
        auto tempfile = unique_ptr<fstream>(new fstream(filename, fstream::in | fstream::out | fstream::trunc));
        for (auto i: vector)
            (*tempfile) << i << " ";
        
        tempfiles.push_back(pair<decltype(tempfile), string>(std::move(tempfile), filename));
    }

    auto listIterPrev = tempfiles.begin(), listIter = ++ tempfiles.begin();
    for(; listIter != tempfiles.end(); ++ ++ listIter, ++ ++ listIterPrev)
    {
        // merge
        auto & file1 = listIterPrev->first;
        auto & file2 = listIter->first;
        file1->seekg(fstream::beg);
        file2->seekg(fstream::beg);
        
        // create a new file
        auto filename = temp_name + boost::lexical_cast<string>(temp_number++);
        auto tempfile = unique_ptr<fstream>(new fstream(filename, fstream::in | fstream::out | fstream::trunc));
        int temp;
        (*file1) >> temp;

        bool getFromFirst = false;
        
        cout << listIterPrev->second << " " << listIter->second << endl;
                  
        // merge two files
        while (true)
        {
            auto & file = getFromFirst ? file1: file2;
            int value;
            // read from a file
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
    rename(listIterPrev->second.c_str(), output_file_name.c_str());

    return 0;
}
    
   