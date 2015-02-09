#include <cstdlib>
#include <iostream>
#include <time.h>
 
using namespace std;
 
int vett[9],scelta,i,fine,ctrl,risultato;
void legenda(),visualizza(),input(),random(),controllo_a(),controllo_b();
 
main()
{
    cout<<"TRIS\n\n";
    srand(time(NULL));
    legenda();
    while(fine==false)
    {
        controllo_a();
        controllo_b();
        if(ctrl!=9)
        {
            input();
            visualizza();
        }
        else
            fine=true;
        system("cls");
        controllo_a();
        controllo_b();
        if(ctrl!=9)
        {
            random();
            visualizza();
        }
        else
            fine=true;
    }
    cout<<endl;
    visualizza();
    cout<<endl;
    switch(risultato)
    {
        case 1:
            cout<<"\n\nHAI VINTO\n\n";
            break;
        case 2:
            cout<<"\n\nHAI PERSO\n\n";
            break;
        default:
            cout<<"\n\nPAREGGIO\n\n";
            break;
    }
    cout<<endl<<endl;
    system("pause");
}
 
void input()
{
    cout<<endl<<endl<<"inserisci la tua x [1-9]: ";
    cin>>scelta;
    while(scelta==0)
    {
        legenda();
        cout<<"inserisci la tua x: ";
        cin>>scelta;
    }
    scelta--;
    while(vett[scelta]!=0)
    {
        cout<<"casella gia in uso,reinserisci la tua x: ";
        cin>>scelta;
        while(scelta==0)
        {
            legenda();
            cout<<"inserisci la tua x: ";
            cin>>scelta;
        }
        scelta--;
    }
    vett[scelta]=1;
}
 
void random()       //decisione cpu intelligente
{
    if(vett[0]==vett[1] && vett[0]!=0)
    {
        scelta=2;
    }
    if(vett[3]==vett[4] && vett[3]!=0)
    {
        scelta=5;
    }
    if(vett[6]==vett[7] && vett[6]!=0)
    {
        scelta=8;
    }
    if(vett[0]==vett[3] && vett[0]!=0)
    {
        scelta=6;
    }
    if(vett[1]==vett[4] && vett[1]!=0)
    {
        scelta=7;
    }
    if(vett[2]==vett[5] && vett[2]!=0)
    {
        scelta=8;
    }
    if(vett[0]==vett[4] && vett[0]!=0)
    {
        scelta=8;
    }
    if(vett[2]==vett[4] && vett[2]!=0)
    {
        scelta=6;
    }
    if(vett[2]==vett[1] && vett[2]!=0)
    {
        scelta=0;
    }
    if(vett[2]==vett[0] && vett[2]!=0)
    {
        scelta=1;
    }
    if(vett[0]==vett[6] && vett[0]!=0)
    {
        scelta=3;
    }
    if(vett[3]==vett[6] && vett[3]!=0)
    {
        scelta=0;
    }
    if(vett[5]==vett[4] && vett[4]!=0)
    {
        scelta=3;
    }
    if(vett[3]==vett[5] && vett[3]!=0)
    {
        scelta=4;
    }
    if(vett[7]==vett[8] && vett[7]!=0)
    {
        scelta=6;
    }
    if(vett[6]==vett[8] && vett[6]!=0)
    {
        scelta=7;
    }
    if(vett[4]==vett[7] && vett[4]!=0)
    {
        scelta=1;
    }
    if(vett[1]==vett[7] && vett[1]!=0)
    {
        scelta=4;
    }
    if(vett[5]==vett[8] && vett[5]!=0)
    {
        scelta=2;
    }
    if(vett[2]==vett[8] && vett[2]!=0)
    {
        scelta=5;
    }
    if(vett[6]==vett[4] && vett[4]!=0)
    {
        scelta=2;
    }
    if(vett[2]==vett[6] && vett[2]!=0)
    {
        scelta=4;
    }
    if(vett[8]==vett[4] && vett[4]!=0)
    {
        scelta=0;
    }
    if(vett[0]==vett[8] && vett[0]!=0)
    {
        scelta=4;
    }
    while(vett[scelta]!=0)
    {
        scelta=rand()%(9);
    }
    vett[scelta]=2;
}
 
void controllo_a()      //controllo pareggio
{
    ctrl=0;
    for(i=0;i<9;i++)
    {
        if(vett[i]!=0)
            ctrl++;
    }
}
 
void controllo_b()      //controllo vincita
{
    if(vett[0]==vett[1] && vett[1]==vett[2] && vett[0]!=0)
    {
        if(vett[0]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[3]==vett[4] && vett[4]==vett[5] && vett[3]!=0)
    {
        if(vett[3]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[6]==vett[7] && vett[7]==vett[8] && vett[6]!=0)
    {
        if(vett[6]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[0]==vett[3] && vett[3]==vett[6] && vett[0]!=0)
    {
        if(vett[0]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[1]==vett[4] && vett[4]==vett[7] && vett[1]!=0)
    {
        if(vett[1]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[2]==vett[5] && vett[5]==vett[8] && vett[2]!=0)
    {
        if(vett[2]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[0]==vett[4] && vett[4]==vett[8] && vett[0]!=0)
    {
        if(vett[0]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(vett[2]==vett[4] && vett[4]==vett[6] && vett[2]!=0)
    {
        if(vett[2]==1)
            risultato=1;
        else
            risultato=2;
    }
    if(risultato==1 || risultato==2)
        ctrl=9;
}
 
void visualizza()       //visualizza il campo
{
    cout<<endl<<endl;
    switch(vett[0])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[1])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[2])
        {
            case 0:
               cout<<"   ";
               break;
            case 1:
                cout<<" x ";
                break;
            case 2:
                cout<<" 0 ";
                break;
        }
        cout<<endl;
        cout<<"---|---|---"<<endl;
        switch(vett[3])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[4])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[5])
        {
            case 0:
               cout<<"   ";
               break;
            case 1:
                cout<<" x ";
                break;
            case 2:
                cout<<" 0 ";
                break;
        }
        cout<<endl;
        cout<<"---|---|---"<<endl;
        switch(vett[6])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[7])
        {
            case 0:
               cout<<"   |";
               break;
            case 1:
                cout<<" x |";
                break;
            case 2:
                cout<<" 0 |";
                break;
        }
        switch(vett[8])
        {
            case 0:
               cout<<"   ";
               break;
            case 1:
                cout<<" x ";
                break;
            case 2:
                cout<<" 0 ";
                break;
        }
}
void legenda()
{
    cout<<"LEGENDA:\n(per visualizzare la leggenda inserire 0)\n\n";
    cout<<" 1 | 2 | 3 "<<endl;
    cout<<"---|---|---"<<endl;
    cout<<" 4 | 5 | 6 "<<endl;
    cout<<"---|---|---"<<endl;
    cout<<" 7 | 8 | 9 "<<endl;
}