#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void menu(){
    cout<<"Choose operation:\n\t[1] Input data\n\t[2] Find records\n\t[3] Modify records\n\t[4] View Class Record\n\t[5] Exit program"<<endl;
	
}


bool detect(int m){
	bool valid;
	switch(m){
		case 1:
			cout<<"-= New Student Record =-";
			valid = true;
			break;
		case 2:
			cout<<"-= View Student Records =-";
			valid = true;
			break;
		case 3:
			cout<<"-= Modify Student Records =-";
			valid = true;
			break;
		case 4:
			cout<<"-= View Class Record =-";
			valid = true;
			break;
		case 5:
			valid = true;
			break;
		default:
			break;
			valid = false;
		}
	return valid;
}

void read(){
	ifstream infile;
	infile.open("class_record.txt");
				string data;
				getline(infile,data,'#');
				cout<<data;
				
}

string newstudent(string output){
	int i;
	cout<<"Student Name: ";
//	cin>>sname;
//	cout<<"\nStudent Number: "<<snum;
return output;
}

int readnumber(string dat){
		std::string data; 
		
		ifstream infile;
		infile.open("class_record.txt");
				getline(infile,data,'#');
			
					int num = std::stoi(data);
				return num;
	}
	


void write(){
		string write;
	//	write = newstudent;
		ofstream outfile;
		outfile.open("class_record.txt", ofstream::app);
		outfile << "Ace Lobos"<< endl;
	
}

int main(){
    string m;
	int n;
	bool valid;
		
	cout<<"Ace grading system"<<endl;
	cout<<"--------------------------------------";
	cout<<"\nNumber of students in class record: ";
	n = readnumber(m);
	cout<<"\n>>"<<endl;
	menu();
	cout<<"Operation:";
	cin>>m;
	valid = detect(m);		
	for (;valid == false;){
	cout<<"\nInvalid Operation.(Undefined)";
	cout<<"\nOperation:";
	cin>>m;
	valid = detect(m);
	}
	if(valid){
		switch (m){
		
				write();
				//operation methods
				break;
			case 2:
				read();
				//operation methods
				break;
			case 3:
				//operation methods
				break;
			case 4:
				//operation methods
				break;
			case 5:
			
				//operation methods
				break;
		}
	}
			
	}
	
	
	
