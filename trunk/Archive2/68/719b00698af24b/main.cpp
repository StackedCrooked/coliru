#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm> //standard algorithms are mainly stored there
#include <numeric>   //some of the number related algorithms stored there
#include <functional> //bind1st, bind2nd, plus<>, minus<>, etc..
#include <iterator> //back_inserter
#include <locale> //tolower

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


int multiply(int value, int multiplier)
{
    return (value * multiplier);
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

int main()
{
    string low = "i have no shift key on my keyboard.";
    cout << "Whisper: " << low << endl;
    
    transform(low.begin(), low.end(), low.begin(), ::toupper);  
    cout << "Shout: " << low << endl;
    
    reverse(low.begin(), low.end());
    cout << "Reversed Shout: " << low << endl;
    
    
    vector<int> scores = createScores();
    vector<int> reverse_scores;
    
    reverse_copy(scores.begin(), scores.end(), back_inserter(reverse_scores));
    cout << "Scores: " << scores << " --- Reversed scores: " << reverse_scores << endl;
    
    list<int> reverse2( scores.rbegin(), scores.rend());
    cout << "Scores: " << scores << " --- Reversed scores #2: " << reverse2 << endl;
    
    //generic swap
    swap(scores, reverse_scores);
    cout << "Swap containers." << endl;
    cout << "Scores: " << scores << " --- Reversed scores: " << reverse_scores << endl;
    
    vector<int>::iterator iter1, iter2;
    iter1 = find(scores.begin(), scores.end(), 5);
    iter2 = find(scores.begin(), scores.end(), 9);
    
    //swap based on iterators
    iter_swap(iter1, iter2);
    cout << "Swap 5 and 9." << endl;
    cout << "Scores: " << scores << endl;
    
    //play with transform
    transform(scores.begin(), scores.end(), scores.begin(), bind2nd(ptr_fun(multiply), 100) );
    cout << "Multiply by 100: " << scores << endl;
    
    //transform with std::negate 
    transform(scores.begin(), scores.end(), scores.begin(), std::negate<int>() );
    cout << "Negate elements: " << scores << endl;
    
    cout << "Minimum element is: " << *min_element(scores.begin(), scores.end()) << endl;
}
