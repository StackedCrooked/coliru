#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;


struct user {

char lname[30];
int userid;
    friend bool operator< (const user& u1, const user& u2);
};

bool operator< (const user& u1, const user& u2)
{
    return strcmp(u1.lname, u2.lname) < 0;
}

user libuser[1000];

int main(){


strcpy(libuser[0].lname,"");
libuser[0].userid = 0;


strcpy(libuser[1].lname,"backzade");
libuser[1].userid = 1;

strcpy(libuser[2].lname,"akhondali");
libuser[2].userid = 2;

    strcpy(libuser[3].lname,"sayidian");
libuser[3].userid = 3;

    strcpy(libuser[4].lname,"navah");
libuser[4].userid = 4;

    strcpy(libuser[5].lname,"mostarab");
libuser[5].userid = 5;


libuser[6].userid = 0;


    strcpy(libuser[7].lname,"");
libuser[7].userid = 0;

    strcpy(libuser[8].lname,"");
libuser[8].userid = 0;

    strcpy(libuser[9].lname,"borobaba");
libuser[9].userid = 9;

    strcpy(libuser[10].lname,"divune");
libuser[10].userid = 10;

   std::sort(std::begin(libuser), std::end(libuser));

for(int i=1;i<1000;i++)
    if(libuser[i].userid!=0)
        cout<<libuser[i].lname<<"\n";




return 0;
}