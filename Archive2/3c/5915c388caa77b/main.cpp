#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}
*/

char getChar(int phoneKey, int j)
{
    //cout<<"phoneKey: "<<phoneKey<<"   j: "<<j<<endl;
    
    if (phoneKey==0)
    {
        return '0';
    }
    else if (phoneKey==1)
    {
        return '1';
    }
    else if (phoneKey==2)
    {
        switch (j)
        {
         case 0:
         return 'A';
         
         case 1:
         return 'B';
         
         case 2:
         return 'C';
        }
    }
    else if (phoneKey==3)
    {
        switch (j)
        {
         case 0:
         return 'D';
         
         case 1:
         return 'E';
         
         case 2:
         return 'F';
        }
    }
    else if (phoneKey==4)
    {
        switch (j)
        {
         case 0:
         return 'G';
         
         case 1:
         return 'H';
         
         case 2:
         return 'I';
        }
    }
    else 
    {
        return 'T';
    }
 
 return 'N';
 
}


void printWord(int* phoneNumber, char* text, int index, int size)
{
    //cout<<"Key: "<<phoneNumber[index]<<endl;
    
    if (index == size)
    {
         //cout<<"printing"<<"  J: "<<j<<endl;
         cout<<text<<endl;
         return;
    }

    
 for (int j=0; j<=2; ++j)
 {
     
     //cout<<"Loop"<<"  J: "<<j<<endl;
     
    text[index] = getChar(phoneNumber[index], j);
    
    printWord(phoneNumber, text, index+1, size);
    
    if (phoneNumber[index]==0 || phoneNumber[index]==1)
    {
        return;
    }
     
 }
 
}

void printTelephoneWordsByRecursion(int phoneNumber[], int size)
{
    //cout<<"Test:  size: "<<size<<"   calculated: "<<sizeof(phoneNumber)/sizeof(phoneNumber[0])<<endl; 
    int index = 0;
    char* text = new char[size+1];
    text[size] = '\0';
    printWord(phoneNumber, text, index, size);
    delete[] text;
}

void printTelephoneWords(int phoneNumber[], int size)
{
    const size_t NUM_OF_OPTIONS = 3;
    std::vector<int> cnt(size,0);
    std::string text(size,' ');                            // use string instead
    //char* text = new char[size+1];
    //text[size] = '\0';
    
    int index;
    for (index=0; index<size; ++index)
    {
        text[index] = getChar(phoneNumber[index], cnt[index]);
    }
    
    index = 0;
    while (index!=size)
    {
        
        if (index==0)
        {
            //text[index] = getChar(phoneNumber[index], cnt[index]);
            
            cout<<"Current: ";
            for (int i=0; i<size; ++i)
            {
                cout<<cnt[i];
            }
            cout<<endl;
        
            cout<<text<<endl;
        }
        
        ++cnt[index];
        text[index] = getChar(phoneNumber[index], cnt[index]);
        
        if(cnt[index]==NUM_OF_OPTIONS)
        {
            cnt[index]=0;
            text[index] = getChar(phoneNumber[index], cnt[index]);
            ++index;
        }
        else
        {
            index = 0;
        }
        
    }
    
    //delete[] text;
}

int main()
{
    /*
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    */
    
    int phoneNumber[] = {2,3};
    int size = sizeof(phoneNumber)/sizeof(phoneNumber[0]);
    //printTelephoneWordsByRecursion(phoneNumber, size);
    printTelephoneWords(phoneNumber, size);
    

}
