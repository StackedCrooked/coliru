#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <limits>

using namespace std;

struct RecAbbo{
    	char name[20];
		char surname[20];
		int games;
		int won;
		int same;
		int lost;
		int place;
		int money;
	}Abbo[100];
void addp();
void sort();
void sear();
void stat();
void game();

void menu();
void safe(RecAbbo structure_name);
void writes(RecAbbo);

int main(){
	fstream in,out;
	in.open("data.txt", ios::in);
	out.open("data.txt", ios::out);
	menu();
	in.close();
	out.close();
	}

void menu(){
	bool exit=false;
	int choise;
	cout<<"welcome \n";
	while (exit == false){
		cout<<"==================================================== \n";
		cout<<"please choose \n";
		cout<<"1. add person \n";
		cout<<"2. sort all accounts\n";
		cout<<"3. search a certain person \n";
		cout<<"4. see the avarage games and statics \n";
		cout<<"5. create random game \n";
		cout<<"0. exit program \n";
		cout<<"==================================================== \n";
		cin>>choise;
		cout<<"==================================================== \n";
		switch (choise){
			case 1:
				addp();
				break;
			case 2: 
				sort();
				break;
			case 3: 
				sear();
				break;
			case 4: 
				stat();
				break;
			case 5: 
				game();
				break;
			case 0: 
				exit=true;
				break;
			default: 
				cout<<"please choose one of the numbers given \n";
				break;
			}
		}
	}
void addp(){
	
	int i;
	while(strcmp(Abbo[i].name, "/0") == 0)
		i++;
	cout<<"name: ";
	cin>>Abbo[i].name;
	cout<<"surname: ";
	cin>>Abbo[i].surname;
	Abbo[i].games = 0;
	Abbo[i].won = 0;
	Abbo[i].same = 0;
	Abbo[i].lost = 0;
	Abbo[i].place = 0;
	Abbo[i].money = 0;
	safe(Abbo);
}
	
void sort(){
	
}

void sear(){
	
}

void stat(){
	int avaragew,avarages,avaragel,avarageg,i=0;
	while (i < 0){
		avaragew = avaragew + Abbo[i].won;
		i++;
	}
	i = 0;
	while (i < 0){
		avarages = avarages + Abbo[i].same;
		i++;
	}
	i = 0;
	while (i < 0){
		avaragel = avaragel + Abbo[i].lost;
		i++;
	}
	i = 0;
	while (i < 0){
		avarageg = avarageg + Abbo[i].games;
		i++;
	}
	avaragew = avaragew/100;
	avarages = avarages/100;
	avaragel = avaragel/100;

	i = 0;
	cout<<"avarage games won				:"<<avaragew<<"%\n";
	cout<<"avarage games with same points			:"<<avarages<<"%\n";
	cout<<"avarage games lost				:"<<avaragel<<"%\n";;
	cout<<"total games played				:"<<avarageg<<" games \n";
}

void game(){
	char name1[20],name2[20],surname1[20],surname2[20];
	int i1, i2, i = 0;
	bool check = false, check2 = false ;
	while (check == false){	
		i1 = rand() % 100;
		i2 = rand() % 100;
		while (check2 == false) 
			if (i1 == i2){
				i2 = (i2 + rand() % 100) - 100;
			} else {
				if (strcmp(Abbo[i1].name, "/0") == 0 || strcmp(Abbo[i2].name, "/0") == 0){
					check2 = false;
				} else {
					check2 = true;
					check = true;
				}
			}
		}
	while (i < 20){
			name1[i] = Abbo[i1].name[i];
			name2[i] = Abbo[i2].name[i];
			surname1[i] = Abbo[i1].surname[i];
			surname2[i] = Abbo[i2].surname[i];
			
			i++;
	}
	Abbo[i1].games++;
	Abbo[i2].games++;
	cout<<"       player 1:     player 2: \n";
	cout<<"game: "<<name1<<surname1<<" VS :"<<name2<<surname2<<endl;
}

void safe(RecAbbo&){
	fstream out;
	out.open("data.txt", ios::out);
	for (int i=0;i<100; i++){
		out << Abbo[i].name << "  \n";
		out << Abbo[i].surname << " \n";
		out << Abbo[i].games << " " << Abbo[i].won << " " << Abbo[i].same << " " << 
		Abbo[i].lost << " " << Abbo[i].place << " " << Abbo[i].money << "\n";
		
	}
}

void writes(){
	fstream in;
	in.open("data.txt", ios::in);
	for (int i=0;i<100; i++){
		in >> std::skipws;  
		in.getline( Abbo[i].name, 20 ).ignore( std::numeric_limits< std::streamsize >::max(), '\n' ); 
		in.getline( Abbo[i].surname, 20 ).ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
		in >> Abbo[i].games >> Abbo[i].won >> Abbo[i].same >> 
        Abbo[i].lost >> Abbo[i].place >> Abbo[i].money;
    }
    in.close();
}
