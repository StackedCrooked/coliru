#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

int main(){
    char ingredientes[][30]={"Arroz","Alberjas","Abichuelas","Pimentones rojos","champiñones","Tomates","Cebollas cabezona","Ajos","Cebollas largas","Colorante","Sal","papas","Queso","Platano","Carne","Salchichas","Pollo","Pez mojarra","Pez bagre","Limones","Naranjas","Moras","Uvas","Ouchuas","Lulos","Maracuyas","guayabas","Tomates de arbol","Vino blanco","Vino rojo","leche"};
    int cantidad[30];
    for(int x=0; x<=30; x++){
            cantidad[x]=2;            
            }
            
    
    
    
	string pass = "", user;
	char ch;
	int num = 3;

	for (int i = 1; i <= num; i++){
        printf("\n\t   vderan's and vedran's\n\tEn donde comer es todo un arte\n\n");
		printf("\nACCESO AL PROGRAMA");
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		cout << "\nOportunidad " << i << " de 3" << "\n";
		printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		cout << "\nIngrese el nombre de usuario: ";
		cin >> user;
		cout << "\nIngrese la contraseña: ";
        ch = _getch();
		

		

		while (ch != 13){
			pass.push_back(ch);
			cout << "*";
			ch = _getch();
		}
		if (pass == "holasoyvedran" && user == "vedran"){
			cout << "\n\nBienvenido mr. " << user << "\n\nACCESO CORRECTO\n\n";
			num = 0;
		}
		else{
			cout << "\n\nError en la contraseña o usuario, intentelo de nuevo.\n\n";
			pass = "";
			user = "";
			system("pause");
			system("cls");
		}
	}
	system("cls");
	printf("\n\t   vderan's and vedran's\n\tEn donde comer es todo un arte\n\n");
    printf("Elija una opcion de administrador:\n1.Rutina preestablecida(1.Revisar inventario de bodega. \n\t\t        2.Subir nuevos datos al sistema. \n\t\t        3.Iniciar turno).\n2.Iniciar turno.\n");
    	
	int opcionentrada1;
    cin>>opcionentrada1;
	switch(opcionentrada1){
                           case 1:
                                
                                int opcionentrada2;
                                opcionentrada2=1;
                                do{
                                printf("RUTINA PREDETERMINADA:\n1.Revisar inventario de bodega.\n2.Subir nuevos datos al sistema.\n3.Iniciar turno.\n");
                                system("pause");
                                system("cls");
                                
                                switch(opcionentrada2){
                                                       case 1:
                                                            printf("1.Revisar inventario de bodega.\n");
                                                            for(int xyz=0; xyz<=27; xyz++){
                                                            printf("\n");        
                                                            cout<<xyz<<". "<< ingredientes[xyz];
                                                            printf("  ");
                                                            cout<< cantidad[xyz]<<" kilogramos";
                                                            printf("\n");
                                                            }
                                                            for(int xyz=28; xyz<=30; xyz++){
                                                            printf("\n");        
                                                            cout<<xyz<<". "<< ingredientes[xyz];
                                                            printf("  ");
                                                            cout<< cantidad[xyz]<<" botellas";
                                                            printf("\n");
                                                            }
                                                       
                                                       
                                                       
                                                       case 2:
                                                            char resp1;
                                                            char resp2;
                                                            printf("----------------------------------------------------------------");
                                                            printf("\n\n2.Subir nuevos datos al sistema.\n\n");
                                                            int axm;
                                                            axm=1;
                                                            for (int intercom1 = 1; intercom1 <=axm ;intercom1++){
                                                            printf("Ingrese el  numero de item que desea cambiar de cantidad: ");
                                                            int xa;
                                                            cin>>xa;
                                                            printf("\n\n");
                                                            cout<<xa<<". "<< ingredientes[xa];
                                                            printf("\nIngrese la nueva cantidad: ");
                                                            int xb;
                                                            cin>>xb;
                                                            cantidad[xa]=xb;
                                                            printf("\tGUARDADO CON EXITO\t\n");
                                                            cout<<ingredientes[xa]<<" "<<cantidad[xa];
                                                            printf("\n\n");
                                                            printf("¿desea ingresar otro dato? s/n: ");
                                                            cin>>resp1;
                                                            printf("\n\n");
                                                            
                                                          if(resp1 == 's'){
                                                                     axm=axm+1;
                                                                     }else{
                                                                           printf("¿Desea ver el inventario de nuevo? s/n: ");
                                                            cin>>resp2;
                                                            printf("\n\n");
                                                            
                                                          if(resp2 == 's'){
                                                                   system("cls");
                                                                   for(int xyz=0; xyz<=27; xyz++){
                                                            printf("\n");        
                                                            cout<<xyz<<". "<< ingredientes[xyz];
                                                            printf("  ");
                                                            cout<< cantidad[xyz]<<" kilogramos";
                                                            printf("\n");
                                                            }
                                                            for(int xyz=28; xyz<=30; xyz++){
                                                            printf("\n");        
                                                            cout<<xyz<<". "<< ingredientes[xyz];
                                                            printf("  ");
                                                            cout<< cantidad[xyz]<<" botellas";
                                                            printf("\n");
                                                            }
                                                            
                                                            
                                                            }
                                                            }
                                                            }
                                                            
                                                       case 3:
                                                            printf("\n\n");
                                                            printf("******************************\n");
                                                            printf("3.Iniciar turno.\n");
                                                            printf("Iniciando . . . .\n\a\a");
                                                            system("pause");
                                                            system("cls");
                                                            
     int finalcost=0;                                                       
     int mko=0;
     int k=0;
     int we=0;
     int acumcuenta=0;
     int axw=0;
     int opsuser;
     int itemabc=0;
     int cuenta[30];
     char platos[][50]={"error","error","error","error","error","error","error","error","error","error","error","CREMA DE POLLO","CREMA DE TOMATE","CREMA DE CEBOLLA","CREMA DE VERDURAS","error","error","error","error","error","error","POLLO A LA PLANCHA","CHURRASCO","MOJARRA","CHULETA DE CERDO","LOMO A LA PLANCHA","ARROZ CON POLLO","error","error","error","error","JUGO DE UVA","JUGO DE MORA","LIMONADA","JUGO DE MARACUYA","JUGO DE TOMATE DE ARBOL","JUGO DE NARANJA","JUGO DE GUAYABA","error","error","error","VINO BLANCO","VINO ROJO"};
     int precios[50];
     char dificultad[][50]={"error","error","error","error","error","error","error","error","error","error","error","FACIL","FACIL","FACIL","MEDIO","error","error","error","error","error","error","MEDIO","MEDIO","MEDIO","MEDIO","MEDIO","DIFICIL","error","error","error","error","MEDIO","FACIL","FACIL","FACIL","FACIL","MEDIO","FACIL","error","error","error","SIN DIFICULTAD","SINDIFICULTAD"};        
     char descripcion[][50]={"","","","","","","","","","","","A base de pollo con finos torzitos de champiñones","","","Es la especialidad de la casa","","","","","","","Plato con 73g de pollo, papas arroz y platano","Plato con 73g de filete, papas arroz y platano","Plato con 73g de mojarra, papas arroz y patacon","Plato con 73g de chuleta, papas arroz y platano","Plato con 73g de lomo, papas arroz y platano","Esta es la especialidad de la casa","","","","","Puede pedirlo con hielo","Puede pedirlo en agua o en leche","Puede pedirla con hielo","Puede pedirlo en agua o en leche","Puede pedirlo con hielo","Puede pedirlo con hielo","Puede pedirlo en agua o leche","","","","Sauvignon Blanc exquisito con carnes rojas","Cabernet Franc especial para cualquier ocasion"};
     char recetas[][50]={"","","","","","","","","","","","Pollo=5g champiñones=5g leche=0.5l","","","Es la especialidad de la casa","","","","","",""," pollo=73g papas=3g arroz=5g platano=2g"," filete=73g papas=3g arroz=5g platano=2g ","mojarra=73g papas=3g arroz=5g patacon=2g ","chuleta=73g papas=3g arroz=5g platano=2g ","lomo=73g papas=3g arroz=5g platano=2g ","(receta secreta)","","","","","uvas=3g","moras=3g","limones=3g","maracuyá=3g","tomates de árbol=3g","naranjas=3g","guayabas=3g","","","","Sauvignon Blanc 100ml","Cabernet Franc 100ml"};
     
     int Ingredientes[50];
     Ingredientes[11]=16043010;
     Ingredientes[12]=300110;
     Ingredientes[13]=300310;
     Ingredientes[14]=30010203;
     Ingredientes[21]=16110013;
     Ingredientes[22]=14110013;
     Ingredientes[23]=17110013;
     Ingredientes[24]=14110013;
     Ingredientes[25]=14110013;
     Ingredientes[26]=0;
     Ingredientes[31]=22;
     Ingredientes[32]=21;
     Ingredientes[33]=19;
     Ingredientes[34]=25;
     Ingredientes[35]=27;
     Ingredientes[36]=20;
     Ingredientes[37]=26;
     Ingredientes[41]=28;
     Ingredientes[42]=29;

     
     precios[11]=5000;    
     precios[12]=5000; 
     precios[13]=5000; 
     precios[14]=5000; 
     precios[21]=15000; 
     precios[22]=17000;
     precios[23]=20000; 
     precios[24]=15000; 
     precios[25]=18000;  
     precios[26]=25000;    
     precios[31]=2000; 
     precios[32]=2000; 
     precios[33]=2000; 
     precios[34]=2000; 
     precios[35]=2000;
     precios[36]=2000; 
     precios[37]=2000; 
     precios[41]=9000;
     precios[42]=9000;
     
     
     
     
     
          
 printf("\n\t   vderan's and vedran's\n\tEn donde comer es todo un arte\n\n");   
 printf("\t\tMenu\n\n***************************");
 printf("\n\n");
 printf("1.CREMAS\n");
 printf("\n\n");
 printf("11.POLLO\n12.TOMATE\n13.CEBOLLA\n14.VERDURAS\n\n");
 
 printf("2.PLATOS A LA CARTA\n\n");
 printf("21.POLLO A LA PLANCHA\n22.CHURRASCO\n23.MOJARRA\n24.CHULETA DE CERDO\n25.LOMO A LA PLANCHA\n26.ARROZ CON POLLO\n\n");
 
 printf("3.JUGOS\n\n");
 printf("31.UVA\n32.MORA\n33.LIMONADA\n34.MARACUYA\n35.TOMATE DE ARBOL\n36.NARANJA\n37.GUAYABA\n\n");
 
 printf("4BEBIDAS\n\n");
 printf("41.VINO BLANCO\n42.VINO ROJO\n\n");

 do{
 printf("ELIJA UNA OPCION DE USUARIO:\n\n1.NUEVA CUENTA.\n2.CUENTA EXISTENTE.\n3.IMPRIMIR FACTURAS.\n4.SALIR.\n");
 cin>>opsuser;
 
 switch(opsuser){
                 
                 case 1:
                 
                 
                 
                 printf("NUEVA CUENTA\n");
                 cuenta[axw];
                 k=1;
                 for(int awq=1; awq<=k;awq++){
                 printf("DIGITE EL CODIGO ASOCIADO AL ITEM ELEGIDO POR EL CLIENTE: ");
                 cin>>itemabc;
                 printf("\n\n");
                 cout<<"Plato: "<<platos[itemabc]<<"\n";
                 cout<<"Precio: "<<precios[itemabc]<<"\n";
                 cout<<"Descripcion: "<<descripcion[itemabc]<<"\n";
                 cout<<"Dificultad: "<<dificultad[itemabc]<<"\n";
                 cout<<"Receta: "<<recetas[itemabc]<<"\n";
                 cout<<"actual en bodega: "<<"\n";
                 int yx3,yx2;
                 yx3=Ingredientes[itemabc];
                 do{
                       
                      yx2=yx3-((yx3/100)*100);                                          
                      yx3=yx3/100;
                      
                      cout<<ingredientes[yx2]<<" "<<cantidad[yx2]<<" kilogramos (en caso de vino o leche botellas de 6L )\n";
                      }while(yx3 != 0); 
                 
                 
                 
                 
                 
                 printf("\nCONFIRMAR? s/n: ");
                 char opfg;
                 cin>>opfg;
                 if( opfg == 'n'){
                                  k=k+1;
                                  }else{
                                         
                                         for(int yu=0;yu<=we;yu++){
                                                 acumcuenta=acumcuenta+itemabc;
                                                 
                                                 }
                                         printf("\nALGO MAS? s/n: ");
                                         char opfgK;
                                         cin>>opfgK;
                                         if( opfgK == 's'){
                                             acumcuenta=acumcuenta*100;
                                             
                                         k=k+1;
                                         }else{ 
                                         
                                         cuenta[axw]=acumcuenta;
                                         printf("su numero de cuenta es: ");
                                         
                                         cout<<axw<<"\n";
                                         printf("\n");
                                         acumcuenta=0;
                                         
                                         axw++;
                                               }
                                  }                 
                 }
                 break;
                 
                 
                 case 2:
                      printf("digite el codigo de la cuenta ");
                      
                      cin>>mko;
                      cuenta[mko]=cuenta[mko]*100;
                      acumcuenta=cuenta[mko];
                      
                 k=1;
                 for(int awq=1; awq<=k;awq++){
                 printf("DIGITE EL CODIGO ASOCIADO AL ITEM ELEGIDO POR EL CLIENTE: ");
                 cin>>itemabc;
                 printf("\n\n");
                 cout<<"Item: "<<platos[itemabc]<<"\n";
                 cout<<"Precio: "<<precios[itemabc]<<"\n";
                 cout<<"Descripcion: "<<descripcion[itemabc]<<"\n";
                 cout<<"Dificultad: "<<dificultad[itemabc]<<"\n";
                 cout<<"Receta: "<<recetas[itemabc]<<"\n";
                 cout<<"actual en bodega: "<<"\n";
                 int yx3,yx2;
                 yx3=Ingredientes[itemabc];
                  do{
                       
                      yx2=yx3-((yx3/100)*100);                                          
                      yx3=yx3/100;
                      
                      cout<<ingredientes[yx2]<<" "<<cantidad[yx2]<<" kilogramos (en caso de vino o leche botellas 6L \n)";
                      }while(yx3 != 0); 
                 
                 
                 
                 
                 
                 printf("\nCONFIRMAR? s/n: ");
                 char opfg;
                 cin>>opfg;
                 if( opfg == 'n'){
                                  k=k+1;
                                  }else{
                                         
                                         for(int yu=0;yu<=we;yu++){
                                                 
                                                 acumcuenta=acumcuenta+itemabc;
                                                 
                                                 }
                                         printf("\nALGO MAS? s/n: ");
                                         char opfgK;
                                         cin>>opfgK;
                                         if( opfgK == 's'){
                                  
                                             acumcuenta=acumcuenta*100;
                                  
                                         k=k+1;
                                         }else{ cuenta[mko]=acumcuenta;
                                         printf("su numero de cuenta es: ");
                                         
                                         cout<<mko<<"\n";
                                         printf("\n");
                                         acumcuenta=0;
                                         
                                               }
                                  }                 
                 }
                 break;
                 
                 
                 case 3:
                      int x;
                      printf("impresion de factura: ");
                      printf("digite el codigo de la cuenta ");
                      int thiscrim;
                      
                      
                      
                      
                      cin>>mko;
                      
                      thiscrim=cuenta[mko];
                      printf("\n\n");
                      
                      do{
                       
                      x=thiscrim-((thiscrim/100)*100);                                          
                      thiscrim=thiscrim/100;
                      
                      cout<<"Item : "<<platos[x]<<" "<<"precio: "<<precios[x]<<"\n\a";
                      finalcost=finalcost+precios[x];
                      
                      
                      }while(thiscrim != 0); 
                      cout<<"Total: "<<finalcost<<"\n\a\a";
                      int paga;
                      printf("Con cuanto cancela? ");
                      cin>>paga;
                      printf("\n");
                      finalcost=paga-finalcost;
                      printf("Su cambio es: ");
                      cout<<finalcost;
                      finalcost=0;
                      printf("\n************VUELVA PRONTO************\n");
                      break;
                      
                 case 4:
                 break;
                 
                 default:
                 printf("la opcion es incorrecta, intentelo de nuevo\n");
                 break;
                         
                      
                 
                      
                      
                      
                     
                 }
  }while(opsuser!=4);               
 
 
                                                       
                                                            
                                                            
                                                            
                                                       
                                                       break;
                                                       
                                                       }opcionentrada2++;
                                   }while(opcionentrada2==4);
                           break;
                                                       
                           case 2:
                                
     int finalcost=0;                            
     int mko=0;
     int k=0;
     int we=0;
     int acumcuenta=0;
     int axw=0;
     int opsuser;
     int itemabc=0;
     int cuenta[30];
     char platos[][50]={"error","error","error","error","error","error","error","error","error","error","error","CREMA DE POLLO","CREMA DE TOMATE","CREMA DE CEBOLLA","CREMA DE VERDURAS","error","error","error","error","error","error","POLLO A LA PLANCHA","CHURRASCO","MOJARRA","CHULETA DE CERDO","LOMO A LA PLANCHA","ARROZ CON POLLO","error","error","error","error","JUGO DE UVA","JUGO DE MORA","LIMONADA","JUGO DE MARACUYA","JUGO DE TOMATE DE ARBOL","JUGO DE NARANJA","JUGO DE GUAYABA","error","error","error","VINO BLANCO","VINO ROJO"};
     int precios[50];
     char dificultad[][50]={"error","error","error","error","error","error","error","error","error","error","error","FACIL","FACIL","FACIL","MEDIO","error","error","error","error","error","error","MEDIO","MEDIO","MEDIO","MEDIO","MEDIO","DIFICIL","error","error","error","error","MEDIO","FACIL","FACIL","FACIL","FACIL","MEDIO","FACIL","error","error","error","SIN DIFICULTAD","SINDIFICULTAD"};        
     char descripcion[][50]={"","","","","","","","","","","","A base de pollo con finos torzitos de champiñones","","","Es la especialidad de la casa","","","","","","","Plato con 73g de pollo, papas arroz y platano","Plato con 73g de filete, papas arroz y platano","Plato con 73g de mojarra, papas arroz y patacon","Plato con 73g de chuleta, papas arroz y platano","Plato con 73g de lomo, papas arroz y platano","Esta es la especialidad de la casa","","","","","Puede pedirlo con hielo","Puede pedirlo en agua o en leche","Puede pedirla con hielo","Puede pedirlo en agua o en leche","Puede pedirlo con hielo","Puede pedirlo con hielo","Puede pedirlo en agua o leche","","","","Sauvignon Blanc exquisito con carnes rojas","Cabernet Franc especial para cualquier ocasion"};
     char recetas[][50]={"","","","","","","","","","","","Pollo=5g champiñones=5g leche=0.5l","","","Es la especialidad de la casa","","","","","",""," pollo=73g papas=3g arroz=5g platano=2g"," filete=73g papas=3g arroz=5g platano=2g ","mojarra=73g papas=3g arroz=5g patacon=2g ","chuleta=73g papas=3g arroz=5g platano=2g ","lomo=73g papas=3g arroz=5g platano=2g ","(receta secreta)","","","","","uvas=3g","moras=3g","limones=3g","maracuyá=3g","tomates de árbol=3g","naranjas=3g","guayabas=3g","","","","Sauvignon Blanc 100ml","Cabernet Franc 100ml"}; 
     
     int Ingredientes[50];
     Ingredientes[11]=16043010;
     Ingredientes[12]=300110;
     Ingredientes[13]=300310;
     Ingredientes[14]=30010203;
     Ingredientes[21]=16110013;
     Ingredientes[22]=14110013;
     Ingredientes[23]=17110013;
     Ingredientes[24]=14110013;
     Ingredientes[25]=14110013;
     Ingredientes[26]=0;
     Ingredientes[31]=22;
     Ingredientes[32]=21;
     Ingredientes[33]=19;
     Ingredientes[34]=25;
     Ingredientes[35]=27;
     Ingredientes[36]=20;
     Ingredientes[37]=26;
     Ingredientes[41]=28;
     Ingredientes[42]=29;
     
     precios[11]=5000;    
     precios[12]=5000; 
     precios[13]=5000; 
     precios[14]=5000; 
     precios[21]=15000; 
     precios[22]=17000;
     precios[23]=20000; 
     precios[24]=15000; 
     precios[25]=18000;  
     precios[26]=25000;    
     precios[31]=2000; 
     precios[32]=2000; 
     precios[33]=2000; 
     precios[34]=2000; 
     precios[35]=2000;
     precios[36]=2000; 
     precios[37]=2000; 
     precios[41]=9000;
     precios[42]=9000;   
     
     
     
          
 printf("\n\t   vderan's and vedran's\n\tEn donde comer es todo un arte\n\n");    
 printf("\t\tMenu\n\n***************************");
 printf("\n\n");
 printf("1.CREMAS\n");
 printf("\n\n");
 printf("11.POLLO\n12.TOMATE\n13.CEBOLLA\n14.VERDURAS\n\n");
 
 printf("2.PLATOS A LA CARTA\n\n");
 printf("21.POLLO A LA PLANCHA\n22.CHURRASCO\n23.MOJARRA\n24.CHULETA DE CERDO\n25.LOMO A LA PLANCHA\n26.ARROZ CON POLLO\n\n");
 
 printf("3.JUGOS\n\n");
 printf("31.UVA\n32.MORA\n33.LIMONADA\n34.MARACUYA\n35.TOMATE DE ARBOL\n36.NARANJA\n37.GUAYABA\n\n");
 
 printf("4BEBIDAS\n\n");
 printf("41.VINO BLANCO\n42.VINO ROJO\n\n");

 do{
 printf("ELIJA UNA OPCION DE USUARIO:\n\n1.NUEVA CUENTA.\n2.CUENTA EXISTENTE.\n3.IMPRIMIR FACTURAS.\n4.SALIR.\n");
 cin>>opsuser;
 
 switch(opsuser){
                 
                 case 1:
                 
                 
                 
                 printf("NUEVA CUENTA\n");
                 cuenta[axw];
                 k=1;
                 for(int awq=1; awq<=k;awq++){
                 printf("DIGITE EL CODIGO ASOCIADO AL ITEM ELEGIDO POR EL CLIENTE: ");
                 cin>>itemabc;
                 printf("\n\n");
                 cout<<"Item: "<<platos[itemabc]<<"\n";
                 cout<<"Precio: "<<precios[itemabc]<<"\n";
                 cout<<"Descripcion: "<<descripcion[itemabc]<<"\n";
                 cout<<"Dificultad: "<<dificultad[itemabc]<<"\n";
                 cout<<"Receta: "<<recetas[itemabc]<<"\n";
                 cout<<"actual en bodega: "<<"\n";
                 int yx3,yx2;
                 yx3=Ingredientes[itemabc];
                  do{
                       
                      yx2=yx3-((yx3/100)*100);                                          
                      yx3=yx3/100;
                      
                      cout<<ingredientes[yx2]<<" "<<cantidad[yx2]<<" kilogramos (en caso de vino o leche botellas 6L \n)";
                      }while(yx3 != 0); 
                 
                 
                 
                 printf("\nCONFIRMAR? s/n: ");
                 char opfg;
                 cin>>opfg;
                 if( opfg == 'n'){
                                  k=k+1;
                                  }else{
                                         
                                         for(int yu=0;yu<=we;yu++){
                                                 acumcuenta=acumcuenta+itemabc;
                                                 
                                                 }
                                         printf("\nALGO MAS? s/n: ");
                                         char opfgK;
                                         cin>>opfgK;
                                         if( opfgK == 's'){
                                             acumcuenta=acumcuenta*100;
                                             
                                         k=k+1;
                                         }else{ 
                                         
                                         cuenta[axw]=acumcuenta;
                                         printf("su numero de cuenta es: ");
                                        
                                         cout<<axw<<"\n";
                                         printf("\n");
                                         acumcuenta=0;
                                         
                                         axw++;
                                               }
                                  }                 
                 }
                 break;
                 
                 
                 case 2:
                      printf("digite el codigo de la cuenta ");
                      
                      cin>>mko;
                      cuenta[mko]=cuenta[mko]*100;
                      acumcuenta=cuenta[mko];
                      
                 k=1;
                 for(int awq=1; awq<=k;awq++){
                 printf("DIGITE EL CODIGO ASOCIADO AL ITEM ELEGIDO POR EL CLIENTE: ");
                 cin>>itemabc;
                 printf("\n\n");
                 cout<<"Item: "<<platos[itemabc]<<"\n";
                 cout<<"Precio: "<<precios[itemabc]<<"\n";
                 cout<<"Descripcion: "<<descripcion[itemabc]<<"\n";
                 cout<<"Dificultad: "<<dificultad[itemabc]<<"\n";
                 cout<<"Receta: "<<recetas[itemabc]<<"\n";
                 cout<<"actual en bodega: "<<"\n";
                 int yx3,yx2;
                 yx3=Ingredientes[itemabc];
                  do{
                       
                      yx2=yx3-((yx3/100)*100);                                          
                      yx3=yx3/100;
                      
                      cout<<ingredientes[yx2]<<" "<<cantidad[yx2]<<" kilogramos (en caso de vino o leche botellas 6L \n)";
                      }while(yx3 != 0); 
                 
                 
                 
                 
                 printf("\nCONFIRMAR? s/n: ");
                 char opfg;
                 cin>>opfg;
                 if( opfg == 'n'){
                                  k=k+1;
                                  }else{
                                         
                                         for(int yu=0;yu<=we;yu++){
                                                 
                                                 acumcuenta=acumcuenta+itemabc;
                                                 
                                                 }
                                         printf("\nALGO MAS? s/n: ");
                                         char opfgK;
                                         cin>>opfgK;
                                         if( opfgK == 's'){
                                  
                                             acumcuenta=acumcuenta*100;
                                  
                                         k=k+1;
                                         }else{ cuenta[mko]=acumcuenta;
                                         printf("su numero de cuenta es: ");
                                         
                                         cout<<mko<<"\n";
                                         printf("\n");
                                         acumcuenta=0;
                                         
                                               }
                                  }                 
                 }
                 
                     break;
                 
                 
                 case 3:
                      int x;
                      printf("impresion de factura: ");
                      printf("digite el codigo de la cuenta ");
                      int thiscrim;
                      
                      
                      
                      
                      cin>>mko;
                      
                      thiscrim=cuenta[mko];
                      printf("\n\n");
                      
                      do{
                       
                      x=thiscrim-((thiscrim/100)*100);                                          
                      thiscrim=thiscrim/100;
                      
                      cout<<"Item : "<<platos[x]<<" "<<"precio: "<<precios[x]<<"\n\a";
                      finalcost=finalcost+precios[x];
                      
                      
                      }while(thiscrim != 0); 
                      cout<<"Total: "<<finalcost<<"\n\a\a";
                      int paga;
                      printf("Con cuanto cancela? ");
                      cin>>paga;
                      printf("\n");
                      finalcost=paga-finalcost;
                      printf("Su cambio es: ");
                      cout<<finalcost;
                      finalcost=0;
                      printf("\n************VUELVA PRONTO************\n");
                      break;
                      
                 case 4:
                 break;
                 
                 default:
                 printf("la opcion es incorrecta intentelo de nuevo\n");
                 break;
                         
                      
                 
                      
                      
                      
                     
                 }
  }while(opsuser!=4);               
 
 
                                
                                
                                
                                
                           break;          
                           }
	
	system("pause");
	return 0;
}