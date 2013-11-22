
#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

//Probability function returns a double < 1
inline double prob(){
       return (static_cast<double>(rand())/RAND_MAX);
}

class Graph{
  public:
         vector < vector < bool > > graph_table; // 2d array created by vectors
         vector < vector < int > > color;        // 2d array created by vectors
         vector < vector < int > > cost;         // 2d array created by vectors
         
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
         void print_graph(void){
              for(unsigned int i=0; i< graph_table.size(); ++i){                 
                      for(unsigned int j=0; j<graph_table.size(); j++){
                              cout << setw(3) << graph_table[i][j] << "(" << color[i][j] << "," << cost[i][j] << ")";
                      }
                      cout << endl;
              }
         }    

};

int main()
{
    string fname;    
    Graph graph(10, 0.2);  
      
    cout << "Enter file name: " << endl;
    cin>>fname;
    graph.read_values_from_file(fname);
    graph.print_graph();
      
    return 1;
}
