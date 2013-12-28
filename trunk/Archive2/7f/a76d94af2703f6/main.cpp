#include <iostream>
#include <thread>
#include <vector>

using namespace std;

int matrix[3][3];
int retMatrix[3][3];

void task(int index)
{
    std::cout<<"task "<<index<<std::endl;
    
    retMatrix[index%3][index/3]=matrix[index/3][index%3];
}

int main()
{
    for(int i=0; i<9; i++)
    {
        matrix[i/3][i%3]=i;
    }
    
    std::vector<std::thread> threads;
    
    for(int i=0; i<9; i++)
    {
        threads.push_back(thread(task, i));
    }
    
    for (std::vector<std::thread>::size_type i=0;i<threads.size(); i++)
    {
        threads[i].join();
    }
    
    for(int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            cout<<retMatrix[i][j];
        }
        cout<<endl;
    }
    
    return 0;
}
