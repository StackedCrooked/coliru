#include <iostream>    	// Basic C++ lib
#include <fstream>		// File Handling lib
#include <ctime> 		// clock time lib

using namespace std;

/* <><> BFS IMPLEMENTATION START <><> */

struct node{
	string name;
	node *parent;
	node *next;
};

class Queue{
	private:
		node *front;
		node *rear;
	public:
		Queue();
		~Queue();
		bool isEmpty();
		void push(node);
		node pop();
		void writeBFS(); 
};


Queue::Queue(){
	front = NULL;
	rear = NULL;	
}

Queue::~Queue(){
	delete front;
}


void Queue::push(node data){
	node *temp = new node();
	temp->name = data.name;
	temp->parent = data.parent;
	temp->next = data.next;
	if(front == NULL){
		front = temp;										//	root 
	}	
	else{
		rear->next = temp->next;
		rear->parent = temp->parent;
	}
	rear = temp;										// push in the queue other than root
}

node Queue::pop(){
	node *temp = new node();
	node value;
	if(front == NULL){
		cout<<"empty quque"<<endl;	
	}
	else{
		temp = front;
		value->name = temp;
		front= front->next;
		delete temp;
	}
	return value;	
}

/* <><> BFS IMPLEMENTATION END <><> */


int numOfNodes=0;

int main(int argc, char** argv) {

	int adjMat[100][100];
	string line,name[100],mat[100];
	ifstream infile("input.txt");
	ofstream tempfile("tempfile.txt");
	
	int namex=0,matx=0,z=0;
	char* tempchar;
	if(infile == NULL)
		perror("Can't open the file");
	else{
	
	// Grabbing node names from input file
			
		while(getline(infile,line)){
			if( (int(line[0])>= 48) && (int(line[0]) <= 57) ) {
				//cout<<"adjancy";
				mat[matx]=line;
				tempfile<<line<<endl;				
				matx++;
			}
			else{
				name[namex]=line;
				namex++;
				numOfNodes++;
			}
		}
		
	}
	tempfile.close();
	
	ifstream tempfile2("tempfile.txt");

	for(int i=0; i<numOfNodes; i++){
		for(int j=0; j<numOfNodes; j++){
			tempfile2>>adjMat[i][j];
		}
		//	cout<<adjMat[i][3]<<endl;
	}
		
		
//	fclose(infile);												// close input file
	infile.close();	
	return 0;
}