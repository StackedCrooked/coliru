#include <queue>
#include <iostream>

using namespace std;

class node { public: int x,y; };

    int bfs(int x, int y)
	{
		node start;
		int result = 0;
		start.x = x;
		start.y = y;
		std::queue<node> search_queue;
		bool visited[4][4];
		int map[4][4] = {
							{0,1,0,1},
							{0,0,0,0},
							{1,0,1,0},
							{0,1,0,0}
						};
		for(int i = 0 ; i < 4; i ++)
		{
			for(int j = 0 ; j < 4; j++)
			{
					visited[i][j] = false;
			}
		}
		search_queue.push(start);
		while(!search_queue.empty())
		{
			node top = search_queue.front();
			search_queue.pop();

			if (visited[top.x][top.y]) continue;
			if (map[top.x][top.y] == 1) continue;
			visited[top.x][top.y] = true;
			result++;
			node temp;

			temp.y = top.y;

			if (top.x < 3)
			{
				temp.x = top.x + 1;
				search_queue.push(temp);
			}

			if (top.x > 0)
			{
				temp.x = top.x - 1;
				search_queue.push(temp);
			}

			temp.x = top.x;

			if (top.y < 3)
			{
				temp.y = top.y + 1;
				search_queue.push(temp);
			}

			if (top.y > 0)
			{
				temp.y = top.y - 1;
				search_queue.push(temp);
			}
		}
		return result;
	}

int main ()
{
	cout << bfs(0, 0) << endl;
}
