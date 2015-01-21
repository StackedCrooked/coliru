#include <iostream>
#include <string>
#include <vector>
#include <algorithm> //standard algorithms are mainly stored there
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

//======= functions ==========

//naive representation
bool isEven(int number)
{
    return (number % 2 == 0);
}

bool isDividableByThree(int number)
{
    return (number % 3 == 0);
}

//template representation!
template <int divisor>
bool isDividableBy(int number)
{
    return (number % divisor == 0);
}

//specify by extra parameter
bool isDividableBy(int number, int divisor)
{
    return (number % divisor == 0);
}

//same as isDividableBy with changed parameters
bool isDividableByAlternate(int divisor, int number)
{
    return isDividableBy(number, divisor);
}


// ========= printers ============
void printEvens(vector<int>& vect)
{
    vector<int>::iterator iter = find_if(vect.begin(), vect.end(), isEven);
    while (iter != vect.end())
    {
        cout << (*iter) << ' ';
        iter++;
        iter = find_if(iter, vect.end(), isEven);     //start of the next search is from the next item
    }
    cout << endl;  
}

void printDividableByThree(vector<int>& vect)
{
    vector<int>::iterator iter = find_if(vect.begin(), vect.end(), isDividableByThree);
    while (iter != vect.end())
    {
        cout << (*iter) << ' ';
        iter++;
        iter = find_if(iter, vect.end(), isDividableByThree);     //start of the next search is from the next item
    }
    cout << endl;      
}

void printDividableByFour(vector<int>& vect)
{
    vector<int>::iterator iter = find_if(vect.begin(), vect.end(), isDividableBy<4>);
    while (iter != vect.end())
    {
        cout << (*iter) << ' ';
        iter++;
        iter = find_if(iter, vect.end(), isDividableBy<4>);     //start of the next search is from the next item
    }
    cout << endl;      
}

void printDividableBy(vector<int>& vect, int divisor)
{
    // isDividableBy<divisor> is not working, as template requires compile time knowledge to generate code
    
    // std::find_if() requires single parameter function, but we have a 2 parameter function: isDividableBy or isDividableByAlternate
    // Lets adjust those functions with an adapter function (bind1st or bind2nd) to convert it to single parameter function;
    // by locking one of the parameter with a given value.
    // unfortunatelly bind1st/bind2nd requires _Operation type as input.
    // so we use ptr_fun to convert normal function to _Operation, then we use bind2nd
    vector<int>::iterator iter = find_if(vect.begin(), vect.end(), 
                                         bind2nd(ptr_fun(isDividableBy), divisor) ); //using bind2nd locks the second parameter with value of divisor for all calls
    while (iter != vect.end())
    {
        cout << (*iter) << ' ';
        iter++;
        iter = find_if(iter, vect.end(), 
                       bind1st(ptr_fun(isDividableByAlternate), divisor) );     //using bind1st is the same, just locking the 1st parameter 
    }
    cout << endl;      
}

int main()
{
    vector<int> scores = createScores();
    cout << scores << endl;
    
    printEvens(scores);            //uses naive function
    printDividableByThree(scores); //uses naive function 
    printDividableByFour(scores);  //use template function
    
    //we can't use template with runtime evaluation so...
    int divisor = 3;
    printDividableBy(scores, divisor);  //use bind2nd and bind1st
    cout << endl;
}
