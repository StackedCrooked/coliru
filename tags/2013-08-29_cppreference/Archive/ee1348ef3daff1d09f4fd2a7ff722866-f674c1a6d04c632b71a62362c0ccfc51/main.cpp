#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <memory>
#include <time.h>
#include <vector>
#include <array>
#include <new> 
#include <map> 
#include <array> 
#include <list> 
#include<algorithm>
#include<fstream>
#include<sstream>//manipuladores
#include<iomanip>//manipuladores
//Hilos no da en mingw
#include<thread>
using namespace std;

/*void f(){
    for(int i=0;i<10;i++)
	{
		printf("%d\n",i);
	}
}*/
void f(const char* s){
	for(int i=0;i<10;i++)
	{
		printf("%s %d\n",s,i);
	}
int main()
{

	//thread p(f)//solo lo hace sin parametros;
	thread q(bind(f,"hola"));
	thread q(f,"hola");
	p.join();
	q.join();
}

