#include <vector>
using namespace std;

struct info{
int num;
int weight;
};
vector<info> nbr;

int main() {
    for(int i=0;i<nbr.size();i++){
        info i = nbr.at(i);
        vector<int> v;
        v.push_back(i.weight);
        tb[i.num] = v;
    }
}