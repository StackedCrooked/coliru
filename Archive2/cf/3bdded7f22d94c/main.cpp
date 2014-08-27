#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define pii pair<int, int>

void nearlystd_store(int val, vector<int> &aVec)//nearly sorted function
{
    vector<int>::iterator Iter;// a vector
    for (int i = 0; i < val; i ++)//generate from the start till desired nvalue
    {
        aVec.push_back(val - i);//push into this vector
    }

    partial_sort(aVec.begin(), aVec.begin() + (val / 2), aVec.end());//sort half in the vector

    for (Iter = aVec.begin(); Iter != aVec.end(); ++Iter)//push sorted value
    {
        aVec.push_back(*Iter);
        delete *Iter;
    }
} 

int main() {

}