#include <iostream>    	// Basic C++ lib
#include <fstream>		// File Handling lib
#include <ctime> 		// clock time lib
#include <queue>		// STL
#include <vector>		// for sorting
#include <algorithm>	// std:sort
#include <stdio.h>		//sizeof
#include <list>			// to sort

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
	int namex=0,matx=0,sourceID=0,destID=0,z=0,p=0,q=0,numOfNodes=0;
	char* tempchar;
	string tempName, outputName, tempParent;
	// stl variables
	string stl_push,stl_pop,sorted_array[100],unsorted_array[100];
	std::queue<string> myqueue;
	int flagg=0;
	list<string> lil;
	list<string>::iterator it,it2;
	
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
				if(line=="Alice"){
					sourceID = namex;
				}
				if(line=="Noah"){
					destID = namex;
				}
				namex++;				
				numOfNodes++;
			}
		}		
	}
cout<<sourceID<<"_"<<destID<<endl;
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

// BFS Implementation


	for(int i=0; i<numOfNodes; i++){
		Nodes[i].name = name[i];								// Name of all nodes defined
		Nodes[i].nodeID = i;									// numbered all the nodes accordingly
		Nodes[i].parent = "NULL";
	}
	/*
	Nodes[0].parent="ROOT";
	for(int i=0; i<numOfNodes; i++){
		for(int j=i; j<numOfNodes; j++){
 			if(adjMat[i][j]!= 0){
 				if(Nodes[j].parent == "NULL"){	
 					Nodes[j].parent = Nodes[i].name;			// parent defined
 					cout<<Nodes[j].name<<"-"<<Nodes[j].parent<<endl;
 				}
 			}
 		}
	}
*/

	it = lil.begin();				// initialize iterator
	
	stl_push=name[0];
	myqueue.push(stl_push);	

	while(p<=numOfNodes){
	
/*
		if(stl_pop == "Noah"){
//			cout<<stl_pop<<" - goal found";
			flagg=1;
			break;
		}
		else{
//			cout<<stl_pop<<" Not goal "<<endl;
			myqueue.pop();
		}

	}
	
		if(flagg == 1){
			break;
		}
*/		
		for(int j=p;j<=numOfNodes;j++){
			if(adjMat[p][j] != 0){
				lil.insert(it,name[j]);
				if(Nodes[j].parent == "NULL")
					Nodes[j].parent = name[p];
//					cout<<name[j]<<"-"<<Nodes[j].parent<<endl;
//				unsorted_array[z] = name[j];
//				stl_push=name[j];
//				myqueue.push(stl_push);							
//				z++;
			}
			else{
//				cout<<"else part:"<<adjMat[p][j]<<"_"<<j<<"-"<<p<<endl;
			}
		}
		lil.sort();
				
		for(it=lil.begin();it != lil.end();it++){			
			//cout<<*it<<endl;
			stl_push=*it;
			myqueue.push(stl_push);									
		}
		lil.clear();

//		cout<<Nodes[p].name<<"-"<<Nodes[p].parent<<endl;
		p++;

		while (!myqueue.empty()){
			stl_pop = myqueue.front();
			myqueue.pop();
		}
}

	for(int x=0; x<numOfNodes; x++){
//		cout<<Nodes[x].name<<"-"<<Nodes[x].parent<<endl;
	}


	tempNode = Nodes[destID];
	pathID[0] = destID;
	cout<<destID;
	for(int x=1,k=destID; x <= numOfNodes-1; x++){
		tempParent = Nodes[k].parent;
		for(int j=numOfNodes-1; j >= 0;j--){
			if(tempParent == Nodes[j].name){
				cout<<j<<" "<<Nodes[j].name<<"_"<<tempParent<<endl;
				k = j;
				q++;
				pathID[q]=k;
				break;
			}
		}
	}
//	q++;
//	pathID[q] = 0;

	for(int i=q; i>=0; i--){
		outputName += Nodes[pathID[i]].name;
		cout<<pathID[q];
		if(i!=0){
		outputName += "-";
		}
	}
	
	outfile<<"Breadth"<<endl;
	outfile << outputName;
	cout<<"out->"<<outputName;		
	outfile.close();
	infile.close();	
	return 0;
}
