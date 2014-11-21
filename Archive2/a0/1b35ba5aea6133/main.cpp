#include<iostream>
#include<array>
#include<vector>

int NullsIn(int r)
{
    int ret=0;
    for(int j=10;j<=r;j*=10)
    {
        if((r/j) * j == r)
            ++ret;
    }
    return ret;
}

int NullsDifference(int r, int m)
{
    return NullsIn(r*m) - NullsIn(r);
}

int backwardIteration(std::array<int,3> state, std::vector<std::vector<int> > const& m)
{
    int i=state[0];
    int j=state[1];
    int r=state[2];
    
    if(i>0 && j>0)
    {
        int inew=i-1;
        int jnew=j-1;
        
        return std::min(NullsDifference(r, m[inew][j]) + backwardIteration({inew,j,r*m[inew][j]}, m),
                        NullsDifference(r, m[i][jnew]) + backwardIteration({i,jnew,r*m[i][jnew]}, m));
        
    }
    else if(i>0)
    {
        int inew=i-1;
        return NullsDifference(r, m[inew][j]) + backwardIteration({inew,j,r*m[inew][j]}, m);
    }
    else if(j>0)
    {
        int jnew=j-1;
        return NullsDifference(r, m[i][jnew]) + backwardIteration({i,jnew,r*m[i][jnew]}, m);
    }
    else
    {
        return 0;
    }
}


int main()
{
    int ncols=2;
    int nrows=3;
    std::vector<std::vector<int> > m={{1,2,100}, {5,5,4}};    
    std::array<int,3> initialState = {ncols-1, nrows -1, m[ncols-1][nrows - 1]};
    
    std::cout<<"Minimum number of zeros: "backwardIteration(initialState, m)<<"\n"<<std::endl;
}
    