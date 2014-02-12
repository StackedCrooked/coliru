#include <iostream>    	// Basic C++ lib
#include <fstream>		// File Handling lib
#include <ctime> 		// clock time lib
#include <queue>		// STL

using namespace std;

struct node{
	string name;
	string parent;
	int nodeID;
};


int main(int argc, char** argv) {

	int adjMat[100][100],pathID[100];
	string line,name[100],mat[100];
	ifstream infile("input.txt");
	ofstream tempfile("tempfile.txt");
	ofstream outfile("output.txt");
	node Nodes[100],tempNode;
	int namex=0,matx=0,z=0,p=0,numOfNodes=0;
	char* tempchar;
	string tempName, outputName, tempParent;
	
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

// close tempfile
	tempfile.close();
// open tempfile in read mode	
	ifstream tempfile2("tempfile.txt");
// Extract the adj Matrix 
	for(int i=0; i<numOfNodes; i++){
		for(int j=0; j<numOfNodes; j++){
			tempfile2>>adjMat[i][j];
		}
	}

		
// BFS implementation

	for(int i=0; i<numOfNodes; i++){
		Nodes[i].name = name[i];								// Name of all nodes defined
		Nodes[i].nodeID = i;									// numbered all the nodes accordingly
		Nodes[i].parent = "NULL";
	}
	for(int i=0; i<numOfNodes; i++){
		for(int j=i; j<numOfNodes; j++){
 			if(adjMat[i][j]!= 0){
 				if(Nodes[j].parent == "NULL"){	
 					Nodes[j].parent = Nodes[i].name;			// parent defined
 				}
 			}
 		}
	}
	
	tempNode = Nodes[numOfNodes - 1];
	pathID[0] = numOfNodes-1;

	for(int x=1,k=numOfNodes-1; x <= numOfNodes-1; x++){
		tempParent = Nodes[k].parent;
		for(int j=numOfNodes-1; j >= 0;j--){
			if(tempParent == Nodes[j].name){
				k = j;
				p++;
				pathID[p]=k;
				break;
			}
		}
	}
	pathID[p] = 0;

	for(int i=p; i>=0; i--){
		outputName += Nodes[pathID[i]].name;
		if(i!=0){
		outputName += "-";
		}
	}
	outfile<<"Breadth"<<endl;
	outfile << outputName;		
	outfile.close();
	infile.close();	
	return 0;
}