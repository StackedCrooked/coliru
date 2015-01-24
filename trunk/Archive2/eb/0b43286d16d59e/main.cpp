#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include <list>

using namespace std;

class Node
{
    public:
    
        Node(int x, int y)
        {
            xpos = x;
            ypos = y;
        
        }
        
        int getX()
        {
            return xpos;   
        }
        
        int getY()
        {
            return ypos;   
        }
        
        int getG()
        {
            return gValue;   
        }
        
        int getF()
        {
            return fValue;   
        }
        
        int getH(Node* aNode, Node* destination)
        {
               int hValue;
               
               int dX = abs(aNode->getX() - destination->getX());
               int dY = abs(aNode->getX() - destination ->getY());
               
               if(dX > dY)
               {
                   hValue = ((14 * dY) + (10 * (dX - dY)));
               }
               
               else
               {
                   hValue = ((14 * dX) + (10 * (dY - dX)));
               }
               
               return hValue;
               
               
        }
        
        bool isChecked()
        {
            return checked;   
        }
        
        void Checked(bool flag)
        {
            checked = flag;
        }
        
        void setG(int g)
        {
            gValue = g;   
        }
        
        void setF(int f)
        {
            fValue = f;   
        }
        
        
    
    private:
    
        int xpos;
        int ypos;
        
        int gValue;
        int fValue;
        
        bool checked;
        
};

class Graph
{
    
    
     public:
        
        Graph(int size)
        {
            graphSize = size;
            for(int i = 0; i < graphSize; i++)
            {
                for(int j = 0; j < graphSize; j++)
                {
                     Node* newNode = new Node(i, j);
                     graph.push_back(newNode);
                }
            }
        }
        
        int sizeOfGraph()
        {
            return graphSize;   
        }
        
        Node* getNode(int x, int y)
        {
            for(vector<Node* >::iterator iter = graph.begin(); iter != graph.end(); iter++)
            {
                if((*iter)->getX() == x && (*iter)->getY() == y)
                {
                    return *iter;   
                }
            }
        }
     
    
     private:
        
        int graphSize;
 
        vector<Node* > graph;
 
};

class compare
{
    public:
    
    bool operator()(Node* lhs, Node* rhs)
    {
           return (lhs->getF() > rhs->getF());
    }
    
};



class ASTAR
{
    public:
    
        friend class compare;
    
        ASTAR(Node* source, Node* dest, Graph& G)
        {
            int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
            int dy[8] = {0, -1, -1, -1, 0, 1, 1, 1};
            Node* current = NULL;
            Node* neighbor = NULL;
            
            source->setG(0);
            int h = source->getH(source, dest);
            
            source->setF(h + source->getG());
            
            PQ.push(source);
            
            while(!PQ.empty())
            {
                current = PQ.top();
            
                PQ.pop();
            
                for(int i = 0; i < 8; i++)
                {
                    int newX = current->getX() + dx[i];
                    int newY = current->getY() + dy[i];
                
                    neighbor = G.getNode(newX, newY);
                    
                    if(newX < 0 || newX >= G.sizeOfGraph() || newY < 0 || newY >= G.sizeOfGraph()){
                        continue;   
                    }
                    
                    else if(neighbor->isChecked() == true){
                        continue;   
                    }
                    
                    else{
                        if(i % 2 == 1){
                            neighbor->setG(current->getG() + 14);
                        }
                        
                        else{
                            neighbor->setG(current->getG() + 10);
                        }
                        
                        int h = neighbor->getH(neighbor, dest);
                        neighbor->setF(h + neighbor->getG());
                    }
                    
                    
                    
                
                
                }
            }
                
             
            
            
            
        }
        
        
        
        
        
    private:
    
        
        
        priority_queue<Node*, vector<Node*>, compare> PQ;
        list<Node* > Closed;
        
        
        
        
    
};


int main()
{
    int graphSize = 5, startX = 1, startY = 4, finishX = 3, finishY = 2;
    
   // cout << "Enter the size of the graph: ";
    //cin >> graphSize;
    
    Graph newGraph(graphSize);
    
    /*cout << "\nEnter the coordinates of the starting the position!" << endl;
    cout << "X: ";
    cin >> startX;
    
    cout << "\nY: ";
    cin >> startY;
    
    cout << "\nAnd now for the destination coordinates!" << endl;
    cout << "X: ";
    cin >> finishX;
    
    cout << "\nY: ";
    cin >> finishY;*/
    
    ASTAR pathfinder(newGraph.getNode(startX, startY), newGraph.getNode(finishX, finishY), newGraph);
    
   
    return 0;  
}