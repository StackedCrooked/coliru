// writing on a text file
#include <iostream>
using namespace std;

int main () {
    int row, colspace, colstar,num=5;
    cout<<"\n";
    cout<<num<<" pyramid\n";
    for(row=1; row<=num; row++){
        for(colspace = num; colspace<=(num*2)-1; colspace--){
        cout<<" ";
        }
        for(colstar = 1; colstar <=row; colstar++){
        cout<<"* ";
        }
         cout<<"\n";
    }
//   ofstream myfile ("example.txt");
//   if (myfile.is_open())
//   {
//     myfile << "This is a line.\n";
//     myfile << "This is another line.\n";
//     myfile.close();
//   }
//   else cout << "Unable to open file";
  return 0;
}