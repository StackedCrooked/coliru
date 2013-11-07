#include <cstdlib> 
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;
typedef vector<vector<double> > ARRAY2D;


/* 
*
*/

class Graph {

public:
 
      double probability (){
             double val=0.;
             for(int i=0; i<1000; ++i){
                    val += (rand() % 100); 
             }
            return (val/1000.);
      }
      double CostFunction(){
          return (rand() % 91 + 10) / 10.0;
      }
      
      void AddEdge(int i, int j, double density){
            double e;          
            e = (probability() > density)? CostFunction(): 0.;
            edges[i].push_back(e);
            edges[j].push_back(e);
      }
      Graph(int n, double density) {   
          size = n;
          for(int i=0; i<n; ++i){
              edges.push_back(vector<double>());
          }
          for(int i=0; i<n; ++i){
             for(int j=i+1; j<n; ++j){
                  AddEdge(i, j, density);      
             }
          }
      }

      void print(){
          cout << "---";
          for(int i=0; i<size; ++i){
                  cout<< setw(5) << i;
          } 
          cout << endl;
          for(int i=0; i<size; ++i){
            cout<< setw(5) << i;
            for(int j=0; j<size; ++j){
               cout<<setw(5) << edges[i][j];
            }
            cout<<endl;
          }
      }

      ~Graph() {
      }
 private:
      int  size;
      ARRAY2D edges; 

};



int main(){
    srand(time(NULL));
    Graph g(20, 20);
    //g.print();
}
