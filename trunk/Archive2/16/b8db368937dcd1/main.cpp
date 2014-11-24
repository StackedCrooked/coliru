#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <deque>
#include <map>
#include <list>
#include<algorithm>
#include <set>

using namespace std;


string StringTransformer(int intSource){
    return to_string(intSource);
    }

void ConvertToUpper(char& charSource){
    charSource = toupper(charSource);
    }

bool isEven(int intSource){
    return (bool)!(intSource%2);
    }

bool isOdd(int intSource){
    return (bool)intSource%2;
    }

void Exercise1(){
    vector<int> vInt;
    vector<string> vString;
    vInt.push_back(1);
    vInt.push_back(2);
    vString.push_back("start");
    vString.resize(vInt.size());
    transform(vInt.begin(),vInt.end(), vString.begin(), StringTransformer);
    cout<<vString[0]<<endl;
    }

void Exercise2(){
    string myString = "example"; 
    for_each(myString.begin(), myString.end(), ConvertToUpper);
    cout<<myString<<endl;
    }
    
void Exercise3(){
    vector<int> v = {1,5,16,2,7,1044,236,19,99};
    int numberOfEven = 0;
    numberOfEven = count_if(v.begin(),v.end(),isEven);
    cout<<numberOfEven<<endl;
    }
    
void Exercise4(){
    vector<int> v = {1,5,16,2,7,1044,236,19,99};
    int minimum, maximum;
    minimum = *min_element(v.begin(), v.end());
    maximum = *max_element(v.begin(),v.end());
    cout<<"MINIMUM: "<<minimum<<endl;
    cout<<"MAXIMUM: "<<maximum<<endl;
    }

void Exercise5(){
    vector<int> v = {1,5,16,2,7,1044,236,19,99};
    v.erase(remove_if(v.begin(),v.end(),isOdd));
    }

template <typename T>
class myOwnVector{

    private:
        vector<T> v;

    public:
    
    myOwnVector(){}
    
    myOwnVector(vector<T> source){
        v = source;
    }
    
    void push_back(T input){
        v.push_back(input);
        v.sort();
    }
    
    bool empty(){
        return v.empty();
    }

    int size(){
        return v.size();
    }
        
};

void Exercise6(){

    
    }
    
int main(){
    
vector<int> v;
vector<int>::iterator it = v.begin();
//cout<<*it<<endl;
    
 return 0;   
}