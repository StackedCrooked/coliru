#include <cstdlib>
#include <iostream>

using namespace std;


string from_int(int number)
{
stringstream ss;
ss << number;
return ss.str();
}

int main(int argc, char *argv[])
{
    const int n=15;
    int r_l[]={13,12,11,10,9,8,7,6,5,4,3,2,1,1,1,0};
    int s[]={8,7,6,5,4,3,2,1,1,0,0,0,0,0,0,0};    
    int p=10;
    

   // int r_l[n+1]={15,13,11,10,9,8,7,6,5,4,3,2,1,0,0,0};
   // int s[n+1]={10,8,6,4,2,1,1,0,0,0,0,0,0,0,0,0};
   // int p=20;

    int rez[n+1][n+1];
    string rez_s[n+1][n+1];
    string comm[n+1];

    int save_old;   
    int change_old;   
    bool flag=false;

    for (int k=0;k<=n;k++)
    {
     save_old=r_l[k];
     change_old=r_l[0]+s[k]-p;
     
     
     if (save_old < change_old)
         {
           rez[0][k]=change_old;   
           if (flag==false)
           { 
           rez_s[0][k]=from_int(change_old)+"*";
           flag= true;
           comm[0]="Если сохраняем f1(t"+from_int(k)+")="+from_int(save_old)+"; Если меняем f1(t"+from_int(k)+")="+from_int(change_old)+" значит меняем";
           }
           else
           rez_s[0][k]=from_int(change_old);
         
         }
        else
        {
           rez[0][k]=save_old;  
           rez_s[0][k]=from_int(save_old);
        }
        
        
     }

     
     for (int d=1;d<=n;d++)
     {
      flag=false;
       for(int g=0;g<=n;g++)
          {
              
              if (g!=15)  save_old=r_l[g]+rez[d-1][g+1];
else
        save_old=r_l[g]+rez[d-1][g];
      change_old=r_l[0]+s[g]-p+rez[d-1][0];
     
     
     if (save_old < change_old)
         {
           rez[d][g]=change_old;  
           if (flag==false)
           { 
           rez_s[d][g]=from_int(change_old)+"*";    
           flag = true;
           comm[d]="Если сохраняем f"+from_int(d)+"(t"+from_int(g)+")="+from_int(save_old)+"; Если меняем f"+from_int(d)+"(t"+from_int(g)+")="+from_int(change_old)+" значит меняем";
           
           }   
          else
           rez_s[d][g]=from_int(change_old);
         }
        else   
        {
           rez[d][g]=save_old;
           rez_s[d][g]=from_int(save_old);
              
        }
             
          }
          
     }
     cout << "n= "+from_int(n)<<endl;
     cout << "p= "+from_int(p)<<endl;
     cout << "r-l: ";
     for (int i=0;i<=n-1;i++)
     {
      cout <<r_l[i] <<" ";
      }
          
        cout << endl;

      cout << "s: ";
     for (int i=0;i<=n-1;i++)
     {
      cout <<s[i] <<" ";
      }
          
        cout << endl;
        cout << endl;
//cout.width(3);
     for (int i=0;i<=n-1;i++)
     {

       for (int j=0;j<=n;j++)
          {
                
                cout << " " << rez_s[i][j] ;
                }
       cout << endl;
     }

    cout << endl;

     for (int i=0;i<=n-1;i++)
     {
      cout <<comm[i]<< endl;
      }
    return 0;
}
