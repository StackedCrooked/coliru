#include<iostream>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
#include <stdio.h>
#include <string.h>

std::string time;
std::vector<int> time_split;
std::vector<std::string> split;
std::stringstream ss(time);
std::string single;
while(std::getline(ss, single, ':'))
{
	split.push_back(single);
}

//anyway to simplify?? Apparently std::stoi doesn't like empty strings... I somehow should take that into account....
		std::transform(split.begin(),
					split.end(),
					std::back_inserter<std::vector<int> > (time_split),
					[](std::string str) -> int
					{ 
					int ret = 0;
					!str.empty() ? 
						ret = std::stoi(str) : ret;
					return ret;
					});
                    
int main()
{
}