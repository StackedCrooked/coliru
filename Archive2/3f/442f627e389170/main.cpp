#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>

typedef enum days{SUNDAY=1, MONDAY=4, TUESDAY=10}days; //define a new type by the names, and they are in increasing order of integer by default
using namespace std;

//overload the operator + 
inline days operator+(days d){
    return static_cast<days>((static_cast<int> (d) + 1 ) % 7);
}

ostream& operator << (ostream & out, days d){
    switch (d){
        case SUNDAY: out<<"SUN"; break;
        case MONDAY: out<<"MONDAY"; break;
    }
    return out;
}


class point{
    public: 
        //double x, y;
        point(double a, double b){
            x = a;
            y = b;
        } 
        point(){
            x = 0;
            y = 0;
        }
        void setx(double v){
            this->x = v;
        }
        void sety(double v){
            this->y = v;
        }
        
        double getx(){
            return this->x;
        }
        
        double gety(){
            return this->y;
        }
        
    private:
        double x, y;
};
point operator + (point p1, point p2){
    point out(p1.getx()+p2.getx(), p1.gety()+p2.gety());
    return out;
}

ostream& operator << (ostream & out, point  p){
    out << "x axis:" << p.getx() << endl << "y axis: "<< p.gety() << endl;
    return out;
}

// Draw a random graph

double rand_gen(){
    return (((double) rand() / (long(RAND_MAX)+1)));
}

bool ** graph_gen(int size, double prob){
    //srand(time(0));
    bool** graphout = new bool*[size];
    for (int i=0; i<size; i++)
        graphout[i] = new bool[size];
    for (int i=0; i<size;i ++){
        //graphout[i] = new bool[size];
        for (int j=0; j<size; j++){
            if (i==j)
                graphout[i][j] = false;
            else{
                //graphout[i][j] = graphout[j][i] = (rand_gen() < prob);
                graphout[i][j] = (rand_gen() < prob);
                graphout[j][i] = graphout[i][j];
                
            }
            
        }
    }
    return graphout;
    
}

bool isConnected(bool ** graph_in, int size){
    int old_size = 0; 
    int c_size = 0;
    bool * closed = new bool[size];
    bool * open = new bool[size];
    for (int i=0; i<size; i++){
        closed[i] = false;
        open[i] = false;
    }
    open[0] = true;
    while (c_size < size){
        for (int i=0; i<size; i++){
            old_size = c_size;
            if (open[i] && (closed[i] == false)){
                closed[i] = true;
                c_size ++;
                for (int j=0; j<size; j++){
                    open[j] = open[j] || graph_in[i][j];
                }
            }
            
            if (c_size == size)
                return true;
            if (c_size == old_size)
                return false;
        }
        
    }
}


int main()
{
    //printf("Hello Wolrd %d!\n", SUNDAY);
    //point A(2,3);
    point A(2,3);
    point B(3,5);
    srand(time(0));
    //A.x = 1;
    //A.y = 2;
    //point& C;
    //point C = A+B;
    //cout << (A+B) << endl;
    //A.setx(100);
    //point C;
    //cout << C;
    //cout << rand_gen();
    int size = 50;
    //bool** input = graph_gen(5, 0.1);
    //bool a = isConnected(graph_gen(size, 0.1), size);
    //cout << ;
    cout << isConnected(graph_gen(size, 0.8), size) << endl;
    //cout << +MONDAY << endl;
    //cout << TUESDAY;
}
