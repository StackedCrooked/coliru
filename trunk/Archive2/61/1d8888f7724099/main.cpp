#include <vector>
#include <queue>
#include <iostream>

using std::vector;
using std::queue;
using std::cout;
using std::endl;

struct Node
{
    Node(int r, int i)
      : id(i)
      , row(r)
    {}

    explicit Node(int i)
      : id(i)
      , row(0)
    {}

    Node()
      : id(0)
      , row(0)
    {}

    int nextLayer(queue<int>& queue, int& curRow)
    {
        int nextId = queue.front();
        queue.pop();

        for (int i = 0; i < children.size(); i++) {
            if (children[i].id == nextId) {
               if (children[i].row == 0)
                  return children[i].nextLayer(queue, curRow);
               else
                  return children[i].row - 1;
            }
        }

        if (queue.size() == 0) {
            curRow++;
            children.push_back(Node(curRow, nextId));
            return curRow - 1;
        }
        else {
            children.push_back(Node(nextId));
            return children.end()->nextLayer(queue, curRow);
        }
    }

    int id;
    int row;
    vector<Node> children;
};

int main()
{
    queue<int> test;
    int row = 0;
    test.push(1);
    test.push(2);
    test.push(3);

    Node testNode;
    cout << testNode.nextLayer(test, row) << endl;
}
