#include <iostream>
#include <string>
#include <vector>


using namespace std;




int main()
{
    int variable=30;
    switch(variable)
    {
        case 0:
        {
            cout<<"you are failed";
            break;
        }        
        case 30:
        {
            cout<<"You Win"<<endl;
            break;
        }
        default:
        {
            cout<< " none of the above"<<endl;
            break;
        }
    }

}
