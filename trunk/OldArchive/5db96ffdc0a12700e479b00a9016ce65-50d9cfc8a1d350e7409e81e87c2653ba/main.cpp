#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct lista{
    char nombre[20];
	int codigo, cantidad;
	float precio;
}*nota;

struct{
	char nombre[50],direc[50],tel[10];
	float saldo,abono;
	int estatus;
}cliente;

struct{
	char nombre[50],direc[50],tel[10];
	int numero,estatus;
	float sueldo;
}empleado;

struct{
	char nombre[50];
	int codigo,existencia,estatus;
	float precio;
}articulo;
//void letras();
int numeros();
int y=1;
float tot=0;
FILE *fich;
FILE *fich2;
FILE *fich3;
FILE *fich4;
FILE *aux;
void clientes();
void empleados();
void articulos();
void proveedor(int reg);
void ticket();
void comprar(int c, int reg);
void altas(int c);
void status(int c,int reg);
void modificar(int c, int reg);
void consultar(int c);
void main(){
	nota=(lista*)malloc(sizeof(lista));
	
	if((fich=fopen("Clientes.dat","a+b"))==NULL){
		printf("No se pudo crear el fichero");
		getch();
		exit(0);
	}
	if((fich2=fopen("Empleados.dat","a+b"))==NULL){
		printf("No se pudo crear el fichero");
		getch();
		exit(0);
	}
	if((fich3=fopen("Articulos.dat","a+b"))==NULL){
		printf("No se pudo crear el fichero");
		getch();
		exit(0);
	}
	if((fich4=fopen("Proveedor.dat","a+b"))==NULL){
		printf("No se pudo crear el fichero");
		getch();
		exit(0);
	}
	char op;
	do{
		clrscr();
		printf("Coppel!\n");
		printf("1.-Clientes\n");
		printf("2.-Empleados\n");
		printf("3.-Articulos\n");
		printf("4.-Salir\n");
		printf("Seleccione una opcion: ");
		scanf("%c",&op);
		switch(op){
			case'1': clientes(); break;
			
			case'2': empleados(); break;
			
			case'3': articulos(); break;
		}
	}while(op!='4');
	fclose(fich);
	fclose(fich2);
	fclose(fich3);
	fclose(fich4);
}
void clientes(){
	int x,c=1;
	char o;
	do{
		clrscr();
		printf("Menu de Clientes\n");
		printf("1.-Alta\n");
		printf("2.-Estatus (A/B)\n");
		printf("3.-Ventas\n");
		printf("4.-Consulta\n");
		printf("5.-Modificar\n");
		printf("6.-Notas\n");
		printf("7.-Salir...");
		scanf("%c",&o);
		switch(o){
			case'1': altas(c); break;
			
			case'2': consultar(c);
			printf("\nIndique Cliente a cambiar estatus: ");
			x=numeros();status(c,x);break;
			
			case'3': consultar(3);
			printf("\nIndique Articulo a Vender: ");
			x=numeros(); comprar(3,x);break;
			
			case'4': consultar(c); getch(); break;
			
			case'5': consultar(c);
			printf("\nIndique Cliente a modificar: ");
			x=numeros(); modificar(c,x);break;
			
			case'6': ticket();break;
		}
	}while(o!='7');
}
void empleados(){
	int x,c=2;
	char o;
	do{
		clrscr();
		printf("Menu de Empleados\n");
		printf("1.-Alta\n");
		printf("2.-Estatus (A/B)\n");
		printf("3.-Modificar\n");
		printf("4.-Consulta\n");
		printf("5.-Salir...");
		scanf("%c",&o);
		switch(o){
			case'1': altas(c); break;
			
			case'2': consultar(c);
			printf("\nIndique Empleado a cambiar estatus: ");
			x=numeros(); status(c,x);break;
			
			case'3': consultar(c);
			printf("\nIndique Empleado a Modificar: ");
			x=numeros(); modificar(c,x);break;
			
			case'4': consultar(c);getch();break;
		}
	}while(o!='5');
}

void articulos(){
	int x,c=3;
	char o;
	do{
		clrscr();
		printf("Menu de Articulos\n");
		printf("1.-Alta\n");
		printf("2.-Estatus (A/B)\n");
		printf("3.-Modificar\n");
		printf("4.-Consulta\n");
		printf("5.-Proveedor\n");
		printf("6.-Salir...");
		scanf("%c",&o);
		switch(o){
			case'1': altas(c); break;
			
			case'2': consultar(c); 
			printf("\nIndique Articulo a cambiar estatus: ");
			x=numeros(); status(c,x); break;
			
			case'3': consultar(c);
			printf("\nIndique Articulo a modificar: ");
			x=numeros(); modificar(c,x);break;
			
			case'4': consultar(c); getch(); break;
			
			case'5': consultar(c);
			printf("\nIndique Articulo a Pedir: ");
			x=numeros(); proveedor(x);break;
		}
	}while(o!='6');
}

void altas(int c){
	clrscr();
	switch(c){
		case 1:
		printf("Alta de Cliente \n");
		printf("Nombre: "); scanf("%s",&cliente.nombre);fflush(stdin);
		printf("Direccion: "); scanf("%s",&cliente.direc);fflush(stdin);
		printf("Telefono: "); scanf("%s",&cliente.tel);fflush(stdin);
		cliente.estatus=1;
		cliente.saldo=0;
		cliente.abono=0;
		fwrite(&cliente,sizeof(cliente),1,fich);
		printf("\nAlta Satisfactoria...");
		getch();
		break;
		
		case 2:
		printf("Alta de Empleado \n");
		printf("Nombre: "); scanf("%s",&empleado.nombre);fflush(stdin);
		printf("Direccion: "); scanf("%s",&empleado.direc);fflush(stdin);
		printf("Telefono: "); scanf("%s",&empleado.tel);fflush(stdin);
		printf("Sueldo: $"); empleado.sueldo=numeros();fflush(stdin);
		empleado.estatus=1;
		fwrite(&empleado,sizeof(empleado),1,fich2);
		printf("\n\nAlta Satisfactoria...");
		getch();
		break;
		
		case 3:
		printf("Alta de Articulo \n");
		printf("Descripcion: "); scanf("%s",&articulo.nombre);fflush(stdin);
		printf("Codigo: "); articulo.codigo=numeros();fflush(stdin);
		printf("\nPrecio: $"); articulo.precio=numeros();fflush(stdin);
		printf("\nExistencia: "); articulo.existencia=numeros();fflush(stdin);
		articulo.estatus=1;
		fwrite(&articulo,sizeof(articulo),1,fich3);
		fwrite(&articulo,sizeof(articulo),1,fich4);
		printf("\nAlta Satisfactoria...");
		getch();
		break;
	}
}

void consultar(int c){
	clrscr();
	int i=0;
	switch(c){
		case 1:
		printf("Lista de Clientes!!\n\n");
		rewind(fich);
		printf("#) Nombre\t\tDireccion \tTelefono\tSaldo   Abono\tEstatus\n");
		while(!feof(fich)){
			i++;
			fread(&cliente,sizeof(cliente),1,fich);
			if(feof(fich)) break;
			printf("%i) %s\t\t%s\t\t%s\t\t%.2f    %.2f\t",i,cliente.nombre,cliente.direc,cliente.tel,cliente.saldo,cliente.abono);
			if(cliente.estatus==1)
			printf("Alta\n");
			else 
			printf("Baja\n");
		}
		break;
		
		case 2:
		printf("Lista de Empleados!!\n\n");
		rewind(fich2);
		printf("#) Nombre\tNumero\tDireccion\t\tTelefono\tSaldo\n");
		while(!feof(fich2)){
			fread(&empleado,sizeof(empleado),1,fich2);
			if(feof(fich2)) break;
			if(empleado.estatus==1){
				i++;
				printf("%i) %s\t%i\t%s\t\t%s\t\t%.2f\n",i,empleado.nombre,empleado.numero,empleado.direc,empleado.tel,empleado.sueldo);
			}
		}
		break;
		
		case 3: 
		printf("Lista de Articulos!!\n\n");
		rewind(fich3);
		printf("Nombre\t\tCodigo\t\tPrecio\t\tExistencia\tEstatus\n");
		while(!feof(fich3)){
			i++;
			fread(&articulo,sizeof(articulo),1,fich3);
			if(feof(fich3)) break;
			printf("%i)%s\t\t%i\t\t$%.2f\t\t%i Pz.\t\t",i,articulo.nombre,articulo.codigo,articulo.precio,articulo.existencia);
			if(articulo.estatus==1)
			printf("Alta\n");
			else 
			printf("Baja\n");
		}
		break;
	}
}
void status(int c, int reg)
{
int i=0,p=0;
switch(c){
		case 1:
		rewind(fich);
		fich=fopen("Clientes.dat","rb+");
		while(!feof(fich))
		{
		fread(&cliente,sizeof(cliente),1,fich);
		if(feof(fich))break;
		i++;
		if(i==reg)
			{if(cliente.estatus==1)
				{cliente.estatus=0;}
			else
				{cliente.estatus=1;}
		reg=reg-1;
		fseek(fich,reg*sizeof(cliente),0);
		fwrite(&cliente,sizeof(cliente),1,fich);
		printf("\n Se ha cambiado el estatus del cliente..!");getch();
		break;
			}	
		}
		break;
		
		case 2:
		rewind(fich2);
		fich2=fopen("Empleados.dat","rb+");
		while(!feof(fich2))
		{fread(&empleado,sizeof(empleado),1,fich2);
		if(i==reg)
			{if(empleado.estatus==1)
				{empleado.estatus=0;}
			else
				{empleado.estatus=1;}
		reg=reg-1;
		fseek(fich2,reg*sizeof(empleado),0);
		fwrite(&empleado,sizeof(empleado),1,fich2);
		printf("\n Se ha cambiado el estatus del empleado..!");
		getch();
		break;
			}
		else
			{i=i+1;}}

		if(feof(fich2))
		{printf(" El Empleado no existe.!\n");
		getch();
		}

		break;
		
		
		case 3:
		rewind(fich3);
		fich3=fopen("Articulos.dat","rb+");
		while(!feof(fich3))
		{fread(&articulo,sizeof(articulo),1,fich3);
		if(i==reg)
			{if(articulo.estatus==1)
				{articulo.estatus=0;}
			else
				{articulo.estatus=1;}
		reg=reg-1;
		fseek(fich3,reg*sizeof(articulo),0);
		fwrite(&articulo,sizeof(articulo),1,fich3);
		printf("\n Se ha cambiado el estatus del articulo..!");
		break;
			}
		else
			{i=i+1;}}

		if(feof(fich3))
		{printf(" El Articulo no existe.!\n");
		getch();
		}

		break;
		
	 }
}
void modificar(int c, int reg)
{
int i=0;
switch(c){
		case 1:
		rewind(fich);
		fich=fopen("Clientes.dat","rb+");
		while(!feof(fich))
		{fread(&cliente,sizeof(cliente),1,fich);
		if(i==reg)
			{if(cliente.estatus==1)
				{printf("Nombre: "); scanf("%s",&cliente.nombre);fflush(stdin);
				printf("Direccion: "); scanf("%s",&cliente.direc);fflush(stdin);
				printf("Telefono: "); scanf("%s",&cliente.tel);fflush(stdin);}
			else{
				printf("El Cliente esta dado de baja.!\n");
				getch();
				clientes();}
		reg=reg-1;
		fseek(fich,reg*sizeof(cliente),0);
		fwrite(&cliente,sizeof(cliente),1,fich);
		printf("Se ha modificado el cliente\n");
		break;
			}
		else
			{i=i+1;}}

		if(feof(fich))
		{printf(" El cliente no existe.!\n");
		getch();
		}
		break;
		
		case 2:
		rewind(fich2);
		fich2=fopen("Empleados.dat","rb+");
		while(!feof(fich2))
		{fread(&empleado,sizeof(empleado),1,fich2);
		if(i==reg)
			{if(empleado.estatus==1)
				{printf("Nombre: "); scanf("%s",&empleado.nombre);fflush(stdin);
				printf("Direccion: "); scanf("%s",&empleado.direc);fflush(stdin);
				printf("Telefono: "); scanf("%s",&empleado.tel);fflush(stdin);
				printf("Sueldo: ");scanf("%f",&empleado.sueldo);fflush(stdin);}
			else
				{printf("El Empleado esta dado de baja.!\n");
				getch();
				empleados();}
		reg=reg-1;
		fseek(fich2,reg*sizeof(empleado),0);
		fwrite(&empleado,sizeof(empleado),1,fich2);
		printf("Se ha modificado el Empleado\n");
		break;
			}
		else
			{i=i+1;}}

		if(feof(fich2))
		{printf(" El Empleado no existe.!\n");
		getch();
		}
		break;
		
		
		case 3:
		rewind(fich3);
		fich3=fopen("Articulos.dat","rb+");
		while(!feof(fich3))
		{fread(&articulo,sizeof(articulo),1,fich3);
		if(i==reg)
			{if(articulo.estatus==1)
				{printf("Descripcion: "); scanf("%s",&articulo.nombre);fflush(stdin);
				printf("Codigo: "); articulo.codigo=numeros();fflush(stdin);
				printf("\nPrecio: $"); articulo.precio=numeros();fflush(stdin);
				printf("\nExistencia: "); articulo.existencia=numeros();fflush(stdin);
				
						}
			else
				{printf("El articulo esta dado de baja.!\n");
				getch();
				articulos();}
		reg=reg-1;
		fseek(fich3,reg*sizeof(articulo),0);
		fwrite(&articulo,sizeof(articulo),1,fich3);
		printf("Se ha modificado el Articulo\n");
		break;
			}
		else
			{i=i+1;}}

		if(feof(fich3))
		{printf(" El Articulo no existe.!\n");
		getch();
		}
		break;
		
	 }
}

void comprar(int c, int reg){
	int i=0;
	rewind(fich3);
	while(!feof(fich3)){
		fread(&articulo,sizeof(articulo),1,fich3);
		if(feof(fich3)) break;
		i++;
		if(i==reg){
			nota=(lista*)realloc(nota,y*(sizeof(lista)));
			strcpy(nota[y-1].nombre,articulo.nombre);
			nota[y-1].codigo=articulo.codigo;
			nota[y-1].precio=articulo.precio;
			tot+=nota[y-1].precio;
			y++;
			break;
		}
	}
}

void ticket(){
	int i,reg=1;
	char nombreaux[50];
	clrscr();
	printf("Descripcion\t\tCodigo\t\tPrecio\n");
	for(i=0;i<y-1;i++){
		printf("%s\t\t%i\t\t&%.2f\n",nota[i].nombre,nota[i].codigo,nota[i].precio);
	}
	printf("\nTotal = $%.2f\n",tot);
	printf("Introduzca su nombre: "); scanf("%s",&nombreaux);
	rewind(fich);
	fich=fopen("Clientes.dat","rb+");
	while(!feof(fich)){
		fread(&cliente,sizeof(cliente),1,fich);
		if(feof(fich)){
			printf("\nNombre Inexistente...");
			getch();
			break;
		}
		if((strcmp(nombreaux,cliente.nombre))==0){
			cliente.saldo+=tot;
			cliente.abono+=tot/12;
			tot=0;
			reg=reg-1;
			fseek(fich,reg*sizeof(cliente),0);
			fwrite(&cliente,sizeof(cliente),1,fich);
			break;
		}
		else
		reg=reg+1;
	}
	for(i=0;i<y;i++){
		reg=1;
		rewind(fich3);
		fich3=fopen("Articulos.dat","rb+");
		while(!feof(fich3)){
			fread(&articulo,sizeof(articulo),1,fich3);
			if(feof(fich3)) break;
			if((strcmp(nota[i].nombre,articulo.nombre))==0){
				articulo.existencia--;
				reg=reg-1;
				fseek(fich3,reg*sizeof(articulo),0);
				fwrite(&articulo,sizeof(articulo),1,fich3);
				break;
			}
			else
			reg=reg+1;
		}
	}
	y=1;
}

void proveedor(int reg){
	int i=0,cant;
	printf("\nIndique Cantidad a pedir: ");
	cant=numeros();
	rewind(fich3);
	fich3=fopen("Articulos.dat","rb+");
	while(!feof(fich3)){
		fread(&articulo,sizeof(articulo),1,fich3);
		if(feof(fich3))
		break;
		i++;
		if(i==reg){
			articulo.existencia+=cant;
			reg=reg-1;
			fseek(fich3,reg*sizeof(articulo),0);
			fwrite(&articulo,sizeof(articulo),1,fich3);
			break;
		}
	}	
}

int numeros(){
	char a;
	char num[10];
	int i=0,x=0;
	strcpy(num,"");
	while(a!=13&&i<10){
		a=getch();
		if(a<='9'&&a>='0'){
			printf("%c",a);
			num[i]=a;
			i++;
		}
		else if(a==8){
			if(i>0){
				num[i]=0;
				i--;
				a=0;
				printf("%c%c%c",8,a,8);
			}
		}
	}
	x=atoi(num);
	return x;
}