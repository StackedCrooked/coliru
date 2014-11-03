#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <stdexcept>

using namespace std;
int main()
{ 
    vector<int> wektor(1);
    try
    {
        wektor.at(10)=100; 
    }
    catch(domain_error e)
    {
        cout<<"Domain error"<<endl;
    }
    catch(logic_error e)
    {
        cout<<"Logic_error "<<e.what()<<endl;
        throw;
    }
    catch(exception e)
    {
        cout<<"Exception"<<endl;
    }
    
}
