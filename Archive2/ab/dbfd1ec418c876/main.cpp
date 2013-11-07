#include <iostream>

using namespace std;
#include <vector>

vector<int> entrelace(vector<int> t1, vector<int> t2);
vector<int> tab1({1,2,3});
vector<int> tab2({4,5,6,7,8});
vector<int> mixed;


int main()
{
    mixed=entrelace(tab1,tab2);
}

vector<int> entrelace(vector<int> tab1, vector<int> tab2)
{
	int i(0), m(0);

while(i<tab1.size() or i<tab2.size()){
    if (i<tab1.size()){
        mixed[m++] = tab1[i];};
    if (i < tab2.size()){
        mixed[m++] = tab2[i];}
    i++;
}
return mixed;
}


