#include<iostream>


using namespace std;

class mikey{
    public:
        mikey(int x, int y) : x1(x), y1(y) {}
        
    private:
        int x1; 
        int y1;
};

int main()
{
    int M_x, M_y;
    cin>>M_x;
    cin>>M_y;
    mikey m1(M_x, M_y);
}