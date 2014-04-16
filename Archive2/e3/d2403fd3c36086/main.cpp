#include <iostream>
#include <cmath>
#include <map>
#include <stack>
#include <vector>
#include <set>

using std::sqrt;

int main( int argc, char * argv[] )
{
    if(2>argc){ // checks if size n is availible
        std::cout<< "Please Enter a Size of Sudoku to Solve\n";
        return 1;
    }

    float checkarg=(argc-2)%3; //sees if inputs are a multiple of 3

    if(checkarg!=0){ // inputs are not a mulitple of 3 fails
        std::cout<<"Please enter a size and coordinates of numbers you'd like to set\n";
        return 1;
    }

    int n= atoi(argv[1]); //n of nxn sudoku size
    int root = sqrt(n); //the root of size
    if (root != sqrt(n)){ // if the size has no root then its not a sudoku problem
        std::cout<<"This is not a suitable size for a sudoku\n";
        return 2;
    }

    std::map< std::pair<int,int>,int > insertednumbers;

    int savedsquares= (argc-2)/3; //total number of predefined inputted squares
    int j= 2;

    for(int i = 0;i < savedsquares;i++){// makes map of the inputted squares
        int x = atoi(argv[j]);// gets x coordinate
        j++;
        int y = atoi(argv[j]);// gets y coordinate
        j++;
        int sq = atoi(argv[j]);// gets subsquare number
        j++;
        insertednumbers.insert(std::make_pair(std::make_pair(x,y), sq));
    }

    std::stack<int> solns;
    int trial = 1;

    std::vector< std::set<int> >rows(n); //used to check if number is in row
    std::vector< std::set<int> >cols(n); //used to check if number is in column
    std::vector< std::set<int> >squares(n); //used to check if number is in subsquare

    while (solns.size()<size_t(n*n)){
        int row = solns.size() / n; // tells us what row number is in
        int col = solns.size() % n; // tells us what col number is in
        int square = col/root + root*(row/root); // tells us what square number is in
        if(insertednumbers.count(std::make_pair(row,col))>0){ //checks if coordinate is in map and inserts it
            solns.push(insertednumbers[std::make_pair(row,col)]);
            rows[row].insert(insertednumbers[std::make_pair(row,col)]);
            cols[col].insert(insertednumbers[std::make_pair(row,col)]);
            squares[square].insert(insertednumbers[std::make_pair(row,col)]);
        } else if((rows[row].count(trial)==0)&&(cols[col].count(trial)==0)&&(squares[square].count(trial)==0)){ // Checks if number is in row,col or subsquare
            solns.push(trial);
            rows[row].insert(trial);
            cols[col].insert(trial);
            squares[square].insert(trial);
            trial=1;
        } else{
            trial++;
            while(n<trial){ // if the attempt gets greater than n we make the attempt equal the previos solution and pop the last one of the solutions and erase it in all rows and columns and then add 1 to the attempt to check for the next number if applicable.
                trial=solns.top();

                solns.pop();

                int row = solns.size() / n; // tells us what row number is in
                int col = solns.size() % n; // tells us what col number is in
                int square = col/root + root*(row/root); // tells us what square number is in
                rows[row].erase(trial);
                cols[col].erase(trial);
                squares[square].erase(trial);
                trial++;
            }
        }
    }

    std::stack<int> printsolns;
    int temp;
    while(solns.size()>0){//flips the stack from bottom to top
        temp=solns.top();
        printsolns.push(temp);
        solns.pop();
    }
    
    for(int rowi=0;rowi<n;++rowi){ //printing solution
        for(int coli=0;coli<n;++coli){
            std::cout<<printsolns.top()<<" ";
            printsolns.pop();
        }
        std::cout<<"\n";
    }
}
