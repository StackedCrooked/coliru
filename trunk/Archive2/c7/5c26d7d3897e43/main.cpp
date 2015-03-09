#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int g[3][3] = {{4,1,3},{3,3,3},{3,3,3}};//graph edges

class CompareDistance
{
    public:    
        bool operator()(pair<int,int> n1,pair<int,int> n2)
        {
            return g[n1.first][n1.second] < g[n2.first][n2.second];
       }
};

int main()
{

    priority_queue<pair<int,int>,vector<pair<int,int> >,CompareDistance> pq;


    for(int i = 0 ; i < 3 ; i++)
        for(int j = 0 ; j < 3 ; j++)
            pq.push(pair<int,int>(i,j));

    cout<<"\t"<<g[pq.top().first][pq.top().second];//does not give the correct result

    return 0;
}