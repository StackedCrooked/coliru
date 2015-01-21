#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm> //standard algorithms are mainly stored there
#include <numeric>   //some of the number related algorithms stored there
#include <functional> //bind1st, bind2nd
#include <iterator> //back_inserter

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    typename std::vector<T>::const_iterator iter = vec.begin();
    for (; iter != vec.end(); ++iter)
    {
        os << (*iter) << ' ';
    }
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& vec)
{
    typename std::list<T>::const_iterator iter = vec.begin();
    for (; iter != vec.end(); ++iter)
    {
        os << (*iter) << ' ';
    }
    return os;
}

vector<int> createScores()
{
    vector<int> vect;
    vect.push_back(1);
    vect.push_back(2);
    vect.push_back(3);
    vect.push_back(4);
    vect.push_back(5);
    vect.push_back(6);
    vect.push_back(7);
    vect.push_back(8);
    vect.push_back(9);
    vect.push_back(10);
    return vect;
}

//function for bind2nd
bool isGreater(int number, int comparedTo)
{
    return (number > comparedTo);
}

//functor - we don't need bind2nd, etc... magic
//downside that we have to create a whole object.
class greaterThan
{
    public:
        greaterThan(int compareTo) : mCompareTo(compareTo) {};
        bool operator()(int value) { return (value > mCompareTo); }     //this is a "function call" operator. 
    private:
        int mCompareTo;
};

int main()
{
    
    vector<int> scores = createScores();
    cout << "Vector: " << scores << endl;
    
    //===== Reversing values by creating new collection ===========
    //we want to reverse scores, but we don't know the size of the source. 
    //Lets emulate that with setting the reverse size 0 by default.
    vector<int> reverse_scores;
    reverse_scores.resize(0);


    //reverse_copy(scores.begin(), scores.end(), reverse_scores.begin());     //not enough space to store elements. Process may crash..
    //cout << "Reverse vector: " << reverse_scores << endl;
    
    reverse_copy(scores.begin(), scores.end(), back_inserter(reverse_scores));  //call push_back(value) to store items. Safe.
    cout << "Reverse vector: " << reverse_scores << endl;
    
    
    list<int> scores_list;
    copy(scores.begin(), scores.end(), front_inserter(scores_list));  //calls push_front -> it reverse the order
    cout << "Reverse list: " << scores_list << endl;
                    
}
