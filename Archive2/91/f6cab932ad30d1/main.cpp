#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DataElem{
    float sortKey;
    int x;
    int y;
};

int main(int argc, const char * argv[])
{
    vector<DataElem> list;
    list.push_back(DataElem{1.0f,0,0});
    list.push_back(DataElem{0.5f,0,1});
    list.push_back(DataElem{1.5f,1,1});
    sort(list.begin(), list.end(), [](const DataElem& e1, const DataElem& e2){
        if (e1.sortKey < e2.sortKey){
            return -1;
        }
        return 0;
    });
    for (auto & e:list) {
        cout << e.sortKey<<" "<<e.x<<" "<<e.y<<endl;
    }
    
    
    return 0;
}