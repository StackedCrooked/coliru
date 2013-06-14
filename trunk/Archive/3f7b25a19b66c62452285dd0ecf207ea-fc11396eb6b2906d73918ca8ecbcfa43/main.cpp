#include <vector>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <sstream>
#include <iomanip>





using namespace std;
vector<vector<int> > tablero;
vector<vector<vector<int> > > lista_uno;
vector<vector<vector<int> > > lista_dos;
vector<vector<vector<int> > > lista_tres;
vector<vector<vector<int> > > lista_cuatro;
vector<vector<int> >piluso;
vector<int>lista_negra;


void Dibujar_Tablero(vector<vector<int> >tablero1);
void Tomar_Valor();
void Inicializar(){

vector<int> linea;
for(int f=0;f<6;f++){
for(int r=0;r<7;r++){
linea.push_back(0);

}
tablero.push_back(linea);
}

}




int cuatro(vector<vector<int> > caco,int color){
   int hgugu=0; int hcount=0;int gugu=7;int vcount=0;int cuatrochi=0;
 
for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=3){
            
             if(caco[gugu][hh]==color){
                 
                 if(caco[gugu-1][hh]==color){
                     if(caco[gugu-2][hh]==color){
                         if(caco[gugu-3][hh]==color){
                            cuatrochi=4; 
                         }
                     }
                     
             }
        }
        gugu=gugu-1;
        }}
   for(int hh=0;hh<6;hh++){
        hgugu=0;
        while(hgugu<=3){
            if(caco[hh][hgugu]==color){
               if(caco[hh][hgugu+1]==color){
                if(caco[hh][hgugu+2]==color){ 
                 if(caco[hh][hgugu+3]==color){ 
                    
                cuatrochi=4;
                }   
            }}}
        hgugu=hgugu+1;
        }}  
    
    for(int hh=0;hh<=2;hh++){
        hgugu=0;
        while(hgugu<=3){
            
            if(caco[hh][hgugu]==color){
               if(caco[hh+1][hgugu+1]==color){ 
                if(caco[hh+2][hgugu+2]==color){ 
                if(caco[hh+3][hgugu+3]==color){ 
                cuatrochi=4;
            }
            }
            }}
        hgugu=hgugu+1;
        }}
   for(int hh=0;hh<=2;hh++){
        hgugu=0;
        while(hgugu<=3){
            
         if(caco[hh+3][hgugu]==color){
               if(caco[hh+2][hgugu+1]==color){ 
                if(caco[hh+1][hgugu+2]==color){ 
                if(caco[hh][hgugu+3]==color){ 
                cuatrochi=4;
            }
            }
            }}
        hgugu=hgugu+1;
        
        }}
   
    
    return cuatrochi;
}





vector<vector<int> > cocoliche(vector<vector<vector<int> > >locro,int pos){
    
    for(int w=0;w<8;w++){
     for(int ww=0;ww<8;ww++){
piluso[w][ww]=locro[pos][w][ww];
     }}

    return piluso;
}




int Compro_cuatro(vector<vector<vector<int> > > coco,int color){
int a=0;
for(int ii1=0;ii1<lista_uno.size();ii1++){
if(cuatro(cocoliche(lista_uno,ii1),color)==4){
    a=1;
}
}
return a;
}
int max(vector<int>  list){
    int max=list[0];

    for (int i=1; i<list.size(); i++) {
        if (list[i] > max) {
            max = list[i];       }
    }
    return max;
}
int min(vector<int>  list){
    int min=list[0];

    for (int i=1; i<list.size(); i++) {
        if (list[i] < min) {
            min = list[i];       }
    }
    return min;
    
    
}



    
    







void hacer_lista_jugadas_uno(vector<vector<int> >pepa,int jugador){

    
    int gugu=7;
    
    vector<vector<int> >torno;
    vector<int> linea;
for(int f=0;f<6;f++){
for(int r=0;r<7;r++){
linea.push_back(0);

}
torno.push_back(linea);
}



   
    for(int w=0;w<6;w++){
     for(int ww=0;ww<7;ww++){
torno[w][ww]=pepa[w][ww];
     }}

    
    for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=0){
            if(pepa[gugu][hh]==0){
                if(jugador==2){
                torno[gugu][hh]=2;
                lista_uno.push_back(torno);
                torno[gugu][hh]=0;
                break;
                
            }
            if(jugador==1){
                torno[gugu][hh]=1;
                lista_uno.push_back(torno);
                torno[gugu][hh]=0;
                break;
            }
                
        }
        
        gugu=gugu-1;
        
        
        
    }
    
    
    
    
    
}
 
    
}


void hacer_lista_jugadas_dos(vector<vector<int> >pepa,int jugador){

    
    int gugu=7;
    
    vector<vector<int> >torno;
     vector<int> linea;
for(int f=0;f<8;f++){
for(int r=0;r<8;r++){
linea.push_back(0);

}
torno.push_back(linea);
}



   
    for(int w=0;w<6;w++){
     for(int ww=0;ww<7;ww++){
torno[w][ww]=pepa[w][ww];
     }}
    
    for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=0){
            if(pepa[gugu][hh]==0){
                if(jugador==2){
                torno[gugu][hh]=2;
                lista_dos.push_back(torno);
                torno[gugu][hh]=0;
                break;
                
            }
            if(jugador==1){
                torno[gugu][hh]=1;
                lista_dos.push_back(torno);
                torno[gugu][hh]=0;
                break;
            }
                
        }
        
        gugu=gugu-1;
        
        
        
    }
    
    
    
    
    
}
 
    
}
void hacer_lista_jugadas_tres(vector<vector<int> >pepa,int jugador){

    
    int gugu=7;
    
    vector<vector<int> >torno;
     vector<int> linea;
for(int f=0;f<6;f++){
for(int r=0;r<7;r++){
linea.push_back(0);

}
torno.push_back(linea);
}



   
    for(int w=0;w<6;w++){
     for(int ww=0;ww<7;ww++){
torno[w][ww]=pepa[w][ww];
     }}
    
    for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=0){
            if(pepa[gugu][hh]==0){
                if(jugador==2){
                torno[gugu][hh]=2;
                lista_tres.push_back(torno);
                torno[gugu][hh]=0;
                break;
                
            }
            if(jugador==1){
                torno[gugu][hh]=1;
                lista_tres.push_back(torno);
                torno[gugu][hh]=0;
                break;
            }
                
        }
        
        gugu=gugu-1;
        
        
        
    }
    
    
    
    
    
}
 
    
}
void hacer_lista_jugadas_cuatro(vector<vector<int> >pepa,int jugador){

    
    int gugu=7;
    
    vector<vector<int> >torno;
     vector<int> linea;
for(int f=0;f<6;f++){
for(int r=0;r<7;r++){
linea.push_back(0);

}
torno.push_back(linea);
}



   
    for(int w=0;w<6;w++){
     for(int ww=0;ww<7;ww++){
torno[w][ww]=pepa[w][ww];
     }}
    
    for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=0){
            if(pepa[gugu][hh]==0){
                if(jugador==2){
                torno[gugu][hh]=2;
                lista_cuatro.push_back(torno);
                torno[gugu][hh]=0;
                break;
                
            }
            if(jugador==1){
                torno[gugu][hh]=1;
                lista_cuatro.push_back(torno);
                torno[gugu][hh]=0;
                break;
            }
                
        }
        
        gugu=gugu-1;
        
        
        
    }
    
    
    
    
    
}
 
    
}






int compro_abajo(vector<vector<int> >lolo,int u,int w){
 int a=0;   
  if(u==5){
      
  a=2;    
  }  
  if(u<5){
      if(lolo[u+1][w]!=0){
          a=2;
      }
      else{
          a=3;
      }     
  }  
 
    return a;
}


int evualuador(vector<vector<int> >kiko,int color){
int gugu=7; int vcount=0; int hcount=0; int hgugu=0; 

for(int hh=0;hh<7;hh++){
        gugu=5;
        while(gugu>=3){
             if(kiko[gugu][hh]==color){
                 if(kiko[gugu-1][hh]==0){
                     vcount=vcount+20;
             }
        }
            
            if(kiko[gugu][hh]==color){
                   if(kiko[gugu-1][hh]==color){
                    
                
                    if(kiko[gugu-2][hh]==0){
                        vcount=vcount+85;
                        
                    }
                   if(kiko[gugu-2][hh]==color){
                       
                        
                
                   if(kiko[gugu-3][hh]==0){
                        vcount=vcount+300;
                        
                   }
                   if(kiko[gugu-3][hh]==color){
                        
                   }
                   }}
            }
               
                
                gugu=gugu-1;
        
                
            
           
                
        }
        
        
        
        
    }  
  
    
    for(int hh=0;hh<6;hh++){
        hgugu=0;
        while(hgugu<=3){
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==color){
                if(kiko[hh][hgugu+2]==color){ 
                 if(kiko[hh][hgugu+3]==color){ 
                    
                    
                }   
            }}}
            
            
            
            
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                 if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                    
                hcount=hcount+20;
                }   
            }}}
            
                  
               
                   
        if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==color){ 
                  if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                  if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                      
                hcount=hcount+20;
            }
            }
            }}
           
            if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==color){ 
                    
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                 hcount=hcount+300;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }
               }  
            
               
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               
               
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
             if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh][hgugu+1]==color){ 
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh][hgugu+1]==0 && compro_abajo(kiko,hh,hgugu+1)==2){ 
                if(kiko[hh][hgugu+2]==0 && compro_abajo(kiko,hh,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
                
                hgugu=hgugu+1;
        
                
            
           
                
        }
        
        
        
        
    }   
    
    
   


for(int hh=0;hh<=2;hh++){
        hgugu=0;
        while(hgugu<=3){
            
            if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                
            }
            }
            }}
            
            if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){int lolo=0;
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+300;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }
               }  
            
               
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               
               
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
             if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            
            
            
            
            
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
               if(kiko[hh][hgugu]==0 && compro_abajo(kiko,hh,hgugu)==2){
               if(kiko[hh+1][hgugu+1]==color){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
            if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==color){ 
                if(kiko[hh+3][hgugu+3]==0 && compro_abajo(kiko,hh+3,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            
            if(kiko[hh][hgugu]==color){
               if(kiko[hh+1][hgugu+1]==0 && compro_abajo(kiko,hh+1,hgugu+1)==2){ 
                if(kiko[hh+2][hgugu+2]==0 && compro_abajo(kiko,hh+2,hgugu+2)==2){ 
                if(kiko[hh+3][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
                
                hgugu=hgugu+1;
        
                
            
           
                
        }
        
        
        
        
    }   
    


for(int hh=0;hh<=2;hh++){
        hgugu=0;
        while(hgugu<=3){
            
         if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
               
            }
            }
            }}
            
            if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+20;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+300;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }
               }  
            
               
               if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+300;
            }
            }
            }}
               
               
               if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
             if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            
            
            
            
            
               if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
               if(kiko[hh+3][hgugu]==0 && compro_abajo(kiko,hh+3,hgugu)==2){
               if(kiko[hh+2][hgugu+1]==color){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
            if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==color){ 
                if(kiko[hh][hgugu+3]==0 && compro_abajo(kiko,hh,hgugu+3)==2){ 
                hcount=hcount+60;
            }
            }
            }}
            
            if(kiko[hh+3][hgugu]==color){
               if(kiko[hh+2][hgugu+1]==0 && compro_abajo(kiko,hh+2,hgugu+1)==2){ 
                if(kiko[hh+1][hgugu+2]==0 && compro_abajo(kiko,hh+1,hgugu+2)==2){ 
                if(kiko[hh][hgugu+3]==color){ 
                hcount=hcount+60;
            }
            }
            }}
                
                hgugu=hgugu+1;
        
                
            
           
                
        }
        
        
        
        
        
       
}
 

    
    
    
    return hcount+vcount;
    
    }

void calcular_jugada(vector<vector<int> > coco){

int piru=-1;
int re=0;
int cacho=0;
vector<int> lista_minimos;
vector<int> ubicacion_minimos;
vector<int> lista_ubicacion_minimos;
vector<int>lista_maximos;
vector<int>lista_minimos_2;
vector<int>lista_valores;
lista_minimos.clear();
lista_uno.clear();
lista_dos.clear();
lista_tres.clear();
lista_cuatro.clear();
lista_valores.clear();
lista_maximos.clear();
lista_minimos_2.clear();
lista_minimos.clear();
lista_negra.clear();
int a=-1;
int b=-1;
ubicacion_minimos.clear();
lista_ubicacion_minimos.clear();
hacer_lista_jugadas_uno(coco,2);
for(int ii=0;ii<lista_uno.size();ii++){
if(cuatro(lista_uno[ii],2)==4){
a=ii;
}
hacer_lista_jugadas_dos(lista_uno[ii],1);
for(int jj=0;jj<lista_dos.size();jj++){
if(cuatro(lista_dos[jj],1)==4){
lista_ubicacion_minimos.push_back(-40000);
ubicacion_minimos.push_back(ii);
b=ii;}
hacer_lista_jugadas_tres(lista_dos[jj],2);
lista_valores.clear();
for(int jjj=0;jjj<lista_tres.size();jjj++){
lista_valores.push_back(evualuador(lista_tres[jjj],2)-evualuador(lista_tres[jjj],1));
re=re+1;
}
lista_maximos.push_back(max(lista_valores));
lista_tres.clear();
}
lista_minimos.push_back(min(lista_maximos));
lista_maximos.clear();
lista_dos.clear();
}

for(int yu=0;yu<ubicacion_minimos.size();yu++){
int re=ubicacion_minimos[yu];
int min=lista_ubicacion_minimos[yu];
lista_minimos[re]=min;
}

piru= max(lista_minimos);



int lolo=0;

  for(int u=0;u<lista_uno.size();u++)
 {
  if(lista_minimos[u]==piru){
      lolo=u;
      break;

  }
 }


if(a!=-1){
cout<<"PC Gana"<<endl;
cacho=a;
}
if(a==-1){
cacho=lolo;
}
cout<<"Ficha Jugada :"<<lolo+1<<endl;
cout<<"Cantidad de Jugadas : "<<re<<endl;
Dibujar_Tablero(lista_uno[cacho]);
int tres=-1;
for(int r=0;r<lista_minimos.size();r++){
if(lista_minimos[r]==-40000){
tres++;
}
}
if(tres==lista_minimos.size()){
cout<<"Usted Gana"<<endl;
exit(0);
}

if(a!=-1){
cout<<"PC Gana"<<endl;
exit(0);
}
for(int f=0;f<6;f++){
for(int r=0;r<7;r++){
tablero[f][r]=lista_uno[cacho][f][r];
}
}

Tomar_Valor();
}

void Tomar_Valor(){
cout<<endl;
cout<<endl;
int ficha;
cout<<"Ingrese Ficha a Mover:"<<endl;
cin>>ficha;
int gugu=5;
        while(gugu>=0){
            if(tablero[gugu][ficha-1]==0){
                tablero[gugu][ficha-1]=1;
                break;
            
                }

        
        gugu=gugu-1;
        
        
        
   }
Dibujar_Tablero(tablero);
calcular_jugada(tablero);
}
void Dibujar_Tablero(vector<vector<int> >tablero1){
cout<<endl;
cout<<endl;



cout<<"  ";
cout<<"I"<<" ";
cout<<"1 "<<" "<<"I"<<" "; 
cout<<"2 "<<" "<<"I"<<" "; 
cout<<"3 "<<" "<<"I"<<" "; 
cout<<"4 "<<" "<<"I"<<" "; 
cout<<"5 "<<" "<<"I"<<" "; 
cout<<"6 "<<" "<<"I"<<" "; 
cout<<"7 "<<" "<<"I"<<" "; 
cout<<endl;

for(int x=0;x<6;x++){
cout<<" ";
cout<<" ";
cout<<"I"<<" ";

for(int j=0;j<7;j++){
cout<<tablero1[x][j]<<"  "<<"I"<<" ";
}
cout<<endl;
}





}
int main (int argc, char *argv[]) {

Inicializar();
Dibujar_Tablero(tablero);
calcular_jugada(tablero);


}

