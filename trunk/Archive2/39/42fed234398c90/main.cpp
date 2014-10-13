#include<iostream>
#include <vector>

using Pos = std::pair<int, int>;
int main()
{
    int rows=4,cols=4;
	std::vector<std::vector<char>> Map = 
	{ { '-', '-', '-', '-' },
	{ '*', '*', '*', '-' },
	{ '-', '-', '-', '-' },
	{ '-', '-', '*', '-' }
	};

	Pos start(rows-1,0);
	Pos Goal(0,cols-1);
	char ch = 'a';

	while (start != Goal)
	{
		int x = start.first;
		int y = start.second;
		Map[x][y] = ch++;
		if (x>0 && Map[x - 1][y] == '-')
		{//shomal
			start = std::make_pair(x - 1,y);
		}
		else if (y < cols-1 && Map[x][y+1] == '-')
		{//shargh
			start = std::make_pair(x ,y+1);
		}
		else//blocked
			break;
		
	}
	if (start == Goal)
		Map[Goal.first][Goal.second] = ch;

	for (auto& row : Map)
	{
		for (auto& ch : row)
		{
			std::cout << ch;
		}
		std::cout << '\n';
	}
}