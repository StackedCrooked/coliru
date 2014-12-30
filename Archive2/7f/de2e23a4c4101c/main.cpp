#include <iostream>
#include <iomanip>
 using namespace std;

int main()
{
    int three,four,eleven;

for(int t=0;t<=9;t++)
{
    for(int h=0;h<=9;h++)
    {
        for(int r=0;r<=9;r++)
        {
            for(int e=0;e<=9;e++)
            {          
                for(int f=0;f<=9;f++)
                {
                    for(int o=0;o<=9;o++)
                    {
                        for(int u=0;u<=9;u++)
                        {
                            for(int l=0;l<=9;l++)
                            {
                                 for(int d=0;d<=9;d++)
                                {
                                    for(int v=0;v<=9;v++)
                                    {
                                        for(int n=0;n<=9;n++)
                                        {
                                            three=t*10000+h*1000+r*100+e*10+e*1;
                                            three=t*10000+h*1000+r*100+e*10+e*1;
                                            four=f*1000+o*100+u*10+r*1;
                                            eleven=e*100000+l*10000+e*1000+v*100+e*10+n*1; 
                                
                                            if((three+three+four==eleven) && (t!=h) && (t!=r) && (t!=e) && (t!=f) && (t!=o) && (t!=u) && (t!=l) && (t!=v) && (t!=n) && (h!=r) && (h!=e) && (h!=f) && (h!=o) && (h!=u) && (h!=e) && (h!=l) && (h!=v) && (h!=n) && (r!=e) && (r!=f) && (r!=o) && (r!=u) && (r!=l) && (r!=v) && (r!=n) && (e!=f) && (e!=o) && (e!=u) && (e!=r) && (e!=l) && (e!=v) && (e!=n) && (f!=o) && (f!=u) && (f!=r) && (f!=e) && (f!=l) && (f!=v) && (f!=n) && (o!=u) && (o!=r) && (o!=e) && (o!=l) && (o!=v) && (o!=n) && (u!=r) && (u!=l) && (u!=v) && (u!=n) && (l!=v) && (l!=n) && (v!=n))
                                            {
                                                cout<< "three= "<<three<<"   four= "<<four<<"   eleven= "<<eleven<<endl;
                                                cout<<endl;
                                                cout<< "three + three + four= "<<three + four + three<<" : "<< eleven<< "= eleven"<<endl;
                                                cout<<endl;
                                                cout<<n<<endl;
                                                cout<<endl;
                                            }    
                                                 
                                        }
                                        
                                    }  
                                }
                                
                                
                                
                                
                            }
                            
                            
                            
                            
                        }
                    }
                }
                
            }
        }
    }
}




}

