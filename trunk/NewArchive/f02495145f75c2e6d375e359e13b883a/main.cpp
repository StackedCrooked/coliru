#include <iostream>
#include <stdio.h>
#include <vector>
#include <array>

typedef int cell;

int main()
{
    std::vector < std::vector<cell> >  NodePoints;
    for(int i = 0; i < 16; ++i)
    {
    	std::array<cell, 3> temp = {0*i,1*i,2*i};
	    NodePoints.emplace_back(temp.begin(),temp.end());
    }
	for(auto it = NodePoints.begin(); it != NodePoints.end(); ++it)
	{
		std::vector<cell> x = *it;
		std::cout << x[0] << ":" << x[1] << ":" << x[2] << std::endl;   
	}
    return 0;
}