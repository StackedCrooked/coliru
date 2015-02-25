#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <deque>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main() {
    // TESTING FLOAT REFERENCES
    std::vector<float> s (2, 11);
    float &ns = s[0];
    float &ew = s[1];
    //ns = s[0];
    //ew = s[1];
    
    cout << "s[0] is " << s[0] << endl;
    cout << "s[1] is " << s[1] << endl;
    cout << "ns is " << ns << endl;
    cout << "ew is " << ew << endl;
    cout << "---- After update ----" << endl;
    //ns = 8;
    //ew = 7;
    s[0] = 15;
    s[1] = 14;
    cout << "s[0] is " << s[0] << endl;
    cout << "s[1] is " << s[1] << endl;
    cout << "ns is " << ns << endl;
    cout << "ew is " << ew << endl;
    
    
    
    
    // TESTING VECTORS
    /*
    std::vector<float> weights (9);
    
    //weights(2);
    cout << "elem 1 is " << weights[0] << endl;
    cout << "elem 2 is " << weights[2222] << endl;
    cout << "total elems " << weights.size() << endl;
    */
    
    // TESTING DEQUE (DOUBLE ENDED QUEUES)
    /*
    int i = 0;
    int j = -1;
    j = i++;
    
    cout << "i: " << i << endl;
    cout << "j: " << j << endl;
    
    std::deque<float> saHistory;
    saHistory.clear();
    saHistory.assign(2, 3); */// Initialize 2 elements with the value 3
    //saHistory.push_back(3.0);
    //saHistory.push_back(5.0);
    //cout << "num elems is " << saHistory.size() << endl;
    //cout << "first elem is " << saHistory.front() << endl;
    //cout << "last elem is " << saHistory.back() << endl << endl;
    
    //saHistory.resize(saHistory.size(), 0.0);
    //cout << "num elems is " << saHistory.size() << endl;
    //cout << "first elem is " << saHistory.front() << endl;
    //cout << "last elem is " << saHistory.back() << endl << endl;
    
}