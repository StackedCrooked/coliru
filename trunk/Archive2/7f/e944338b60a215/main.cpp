#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

struct transaction
{
    string item;
    int cost;
};

int main()
{
    transaction buy[100];
    transaction sell[100];
    int price;
    int w, s;
    ifstream myfile.open ("messageBoard.txt");
    ofstream results.open ("results.txt");
    string line;

}
   myfile >> getline(myfile, buy[w], '\n');
        if
    if(!myfile)
      {
        cout<<"Error opening input file"<<endl;
        return -1;
      }
        while(myfile, line)
        {
            if(line.find("wanted") != string::npos);
            {
                getline(myfile,buy[w].item);
                getline(myfile,price);
                stringstream(price) >> buy[w].cost;
            }
        }
        while(myfile, line)
        {
            if(line.find("for sale") != string::npos);
            {
                getline(myfile,buy[s].item);
                getline(myfile,price);
                stringstream(price) >> buy[s].cost;
            }
        }
   for(w=0; w<100; w++)
    {
        for(s=0; s<100; s++)
        {
            if(buy[w].item == sell[s].item && buy[w].cost <= sell[s].cost)
                if (results.is_open())
                {
                    results << buy[w] << " matches " << sell[s] << "\n";
                }
                else
                    cout << "Unable to open output file." << endl;
                buy[w] = 0;
                sell[s] = 0;
        }
    }
    results.close();
return 0;
}