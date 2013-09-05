#include<iostream>
#include<string>

using namespace std;

void printInt(int i,bool newline,string words,int format = 0);

int main()
{
    int i = 24;
    printInt(i,true,"This is your number!",5);
    
    return 0;   
}

void printInt(int i,bool newline,string words,int format)
{
    string output = "";
    
    switch(format)
      {
    case 0: output = words + " (" + to_string(i) + ")";
          break;
    case 1: output = words + "(" + to_string(i) + ")";
         break;
    case 2: output = words + " " + to_string(i);
          break;
    case 3: output = words + to_string(i);
        break;
    case 4: output = to_string(i) + " " + words;
        break;
    case 5: output = to_string(i) + words;
        break;
    }
    
    if(newline)
    {
        cout<<"\n"<<output;
    }
    else
    {
        cout<<output;
    }
   
}