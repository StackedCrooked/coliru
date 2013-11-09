#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

//Probability function returns a double < 1
inline double prob(){
       return (static_cast<double>(rand())/RAND_MAX);
}

struct Edge
{
    int from, to, weight;
	friend bool operator<(Edge a, Edge b)
	{
		return a.weight < b.weight;
	}
};

static int Find(int vertex, vector<int> &parent)
{
        if(parent[vertex]==-1)return vertex;
        return parent[vertex] = Find(parent[vertex], parent); /* Finding its parent as well as updating the parent 
                                                         of all vertices along this path */
}

class Graph{
	public:
		vector < vector < bool > > graph_table; // 2d array created by vectors
		vector < vector < int > > color;        // 2d array created by vectors
		vector < vector < int > > cost;         // 2d array created by vectors
		vector < struct Edge > edges;

		// Use this to resize vectors
		// according to input size
		void resize_vectors(int nodes){
			graph_table.resize( nodes , vector<bool>( nodes , false ) );
			color.resize( nodes , vector<int>( nodes , 0 ) );
			cost.resize( nodes , vector<int>( nodes , 0 ) );   
		}

		// Graph constructor
		Graph(int nodes, double density): graph_table(50,vector <bool> (50)), color(50,vector <int> (50)), cost(50,vector <int> (50)){
			resize_vectors(nodes);
			for(int i=0; i< nodes; ++i){                 
				for(int j=i+1; j<nodes; j++){ 
					graph_table[i][j] = graph_table[j][i] = (prob() < density); 
					color[i][j] = color[j][i] = rand()%3;
					cost[i][j] = cost[j][i] = static_cast< int > (prob()*30);                           
				}
			}                 
		}   

		// Graph deconstructor 
		~Graph(){}
        
        // Function used to convert 2D array 
        // to edge info
		void convert_to_edges(){
			edges.resize(graph_table.size());
			for(unsigned int i=0; i< graph_table.size(); ++i){                 
				for(unsigned int j=0; j<graph_table.size(); j++){
					if(cost[i][j] == 0) continue;
					Edge edge;
					edge.from = i;
					edge.to = j;
					edge.weight = cost[i][j];
					edges.push_back(edge);
				}                
			}    
		}
 
        // Take as input filename
        // and read data into graph
		void read_values_from_file(string fname){
			int i,j,size,line1=0;
			ifstream ifp (fname.c_str(), ios::in);

			if (!ifp.is_open()){
				cout << "Cannot open file: \'" << fname.c_str() << "\'" << endl;
				return; // Cannot read file
			}
			while(!ifp.eof()){
				if(line1==0){
					line1++;
					ifp >> size;
					resize_vectors( size );
					//cout << " size: " << size << endl;
				}else{
					ifp >> i >> j >> size;
					graph_table[i][j] = true;
					cost[i][j] = size;
					//cout << "i: " << i << " j: " << j << " cost: " << size<< endl;
				}
			}
			ifp.close();

		}
        
        // Print created Edges
		void print_edges(void){
			for(vector< struct Edge >::iterator it=edges.begin(); it != edges.end(); ++it){                
				cout << (*it).from << "," << (*it).to << ": " << (*it).weight << endl;             
			}
		}    

        // Print the Graph 2D table
		void print_graph(void){
			for(unsigned int i=0; i< graph_table.size(); ++i){                 
				for(unsigned int j=0; j<graph_table.size(); j++){
					cout << setw(3) << graph_table[i][j] << "(" << color[i][j] << "," << cost[i][j] << ")";
				}
				cout << endl;
			}
		}    

        // Kruskal's algorithm
		void Kruskal(void)//(string fname)
		{     
			unsigned int totalEdges = 0;
            int edgePos=0, sum=0;
			Edge edge; 

			convert_to_edges();
			vector <int > parent(edges.size(), -1);

			sort(edges.begin(), edges.end()); 
			//print_edges(); 			
            //ofstream ifp (fname.c_str(), ios::app);
			while(totalEdges < (edges.size() -1))
			{
				edge = edges[edgePos++];
				int parent1 = Find(edge.from, parent);
				int parent2 = Find(edge.to, parent);
				if(parent1!=parent2)
				{
					cost[edge.from][edge.to] = edge.weight;
					cout << "Vertex: "<<setw(3) << edge.from << " , "<< setw(3) << edge.to << "  cost: " << edge.weight << endl;
					//ifp << "Vertex: "<<setw(3) << edge.from << " , "<< setw(3) << edge.to << "  cost: " << edge.weight << endl;
					sum += edge.weight;
					parent[parent1] = parent2;
                }
				totalEdges++;				
			}
			//ifp << "MST: "<< sum<<endl;
			cout << "MST: "<< sum<<endl;
			//ifp.close();

		}

};

int main()
{
    string fname; 
    
    srand(time(NULL));
    Graph graph(10, 0.2);  
     
    cout << "Enter file name: " << endl;
    cin>>fname;
    graph.read_values_from_file(fname);
    graph.Kruskal();//(fname);
 
    return 1;
}


