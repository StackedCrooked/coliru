#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //standard algorithms are mainly stored there
#include <numeric>   //some of the number related algorithms stored there
#include <functional> //bind1st, bind2nd

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

    //sum(values of scores)
    int init_value = 0;
    cout << "Sum of vector: " << accumulate(scores.begin(), scores.end(), init_value) << endl;
    
    //count the occurence of the value
    int selected_value = 4;
    scores.push_back(selected_value);    //just to make sure that count works.
    cout << "Vector: " << scores << endl;
    cout << "Occurence of " << selected_value << " is " << count(scores.begin(), scores.end(), selected_value) << endl;
    

    scores = createScores();
    //1-4 are fails, count success occurences
    cout << "Succeed [scores 5 or higher]: " << count_if(scores.begin(), scores.end(), bind2nd(ptr_fun(isGreater), 4) ) << endl;    //bind2nd magic
    cout << "Succeed [scores 7 or higher]: " << count_if(scores.begin(), scores.end(), greaterThan(7) ) << endl;    // functor object, what you see is an object creation here with parameter 7.
    
    cout << "Reset vector values with -13. >> ";
    fill(scores.begin(), scores.end(), -13);
    cout << "Vector: " << scores << endl;
    
    scores = createScores();
    cout << "Shuffle the vector. >> ";
    random_shuffle(scores.begin(), scores.end());
    cout << "Vector: " << scores << endl;
     
    cout << "Sort it again. >> ";
    sort(scores.begin(), scores.end());
    cout << "Vector: " << scores << endl;
}
