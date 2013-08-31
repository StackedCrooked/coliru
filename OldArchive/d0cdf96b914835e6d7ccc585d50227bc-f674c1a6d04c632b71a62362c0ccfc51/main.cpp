#include <vector>
#include <iostream>


int main()
{
    std::vector<int> count(200, 0);
    std::vector<std::vector<std::vector<int> > > wholelist(200);
    count[0] = 0;
    std::vector<int> one;
    one.push_back(1);
    wholelist[0].push_back(one);
    int totalsum = 0;
    int index = 0;
    while(index != 199) {
        int currentstep = count[index];
        int currentpower = index+1;
        std::vector<std::vector<int> > list = wholelist[index];
        for(std::vector<int> each : list) {
            for(int number : each) {
                static std::vector<int> copied(each);
                int nextindex = number + currentpower - 1;
                copied.push_back(nextindex + 1);
                if(count[nextindex] == 0) {
                    count[nextindex] = currentstep + 1;
                    wholelist[nextindex].push_back(copied);
                    continue;
                }
                if(count[nextindex] != 0 && count[nextindex] > currentstep + 1) {
                    count[nextindex] = currentstep + 1;
                    wholelist[nextindex].clear();
                    wholelist[nextindex].push_back(copied);
                    continue;
                }
                if(count[nextindex] == currentstep + 1) {
                    wholelist[nextindex].push_back(copied);
                    continue;
                }
            }
        }
        std::cout << count[index] << std::endl;
        index++;

    }

    int sum = 0;
    for(int each : count)
        sum += each;
    std::cout << sum << std::endl;
}