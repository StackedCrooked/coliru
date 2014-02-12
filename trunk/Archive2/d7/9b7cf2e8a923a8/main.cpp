#include <iostream>    	// Basic C++ lib
#include <fstream>		// File Handling lib
#include <algorithm>	// usage of std:find
#include <stdio.h>		//sizeof
#include <list>			// to sort
#include <queue>		// STL - Queue
#include <stack>		// for dfs

using namespace std;

struct node{
	string name;										// Name of the node
	string parent;										// Parent name of the node
	int nodeID,cost;									// 'nodeID' is just a number given to the node. 'cost' is for UCS	
	string discovered,explored; 						// Flags used For DFS
};


int main(int argc, char** argv) {

/**** Do a test of the file first ****/
	int count_nodes = 0;								// to count the total length of the input file
	ifstream testfile("social-network.txt");						// open input file in readable format
	string testString;									
	if(testfile){							
		while(getline(testfile,testString)){			// Store each line into 'testString' and go to next line
			if(int(testString[0]) >= 48 && int(testString[0]) <= 57){
                count_nodes++;							// Increment the count if the line is stored
            }
        }
	}
	else{												// if the 'input.txt' file not found, print error and stop!
		cout<<"Input File not found";
		return 0;
	}

	testfile.close();									// Close the input.txt file once it is tested 
	

/**** Start with the implementation ****/
	//adjMat[][] will hold adjancy matrix.  pathID[] will contain nodeIDs of output path nodes.
/*
	int **adjMat = new int*[count_nodes/2];
	for(int i=0; i<=count_nodes/2; i++){
		adjMat[i]= new int[count_nodes/2];
	}
		
*/
	int adjMat[count_nodes][count_nodes];
	int *pathID = new int[count_nodes];
	// 'line' will contain string ine from input.txt. 
	string line;
	// name[] will contain node names and mat[] will contain adjancy matrix values
	string *name = new string[count_nodes+1];
    string *mat = new string[count_nodes+1];
	ifstream infile("social-network.txt");									// Open input.txt in readable format
	ofstream tempfile("tempfile.txt");								// Create and open tempfile.txt into writable format	
	node *Nodes = new node[count_nodes];

/**** BFS Variables (and some common variables as well) ****/	
	ofstream BFSoutfile("breadth-first.result.txt");							// Create and open BFSoutput.txt into writable format
	int namex=0,matx=0,sourceID=0,destID=0,p=0,q=0,numOfNodes=0,tempp; // Some temporary varaibles
	string tempName, BFSoutputName, tempParent;						// Some temporary variables. 'BFSoututName' to hold output string for BFS.
	string stl_push,stl_pop;
	string *sorted_array = new string[count_nodes];
	string *unsorted_array = new string[count_nodes];
	std::queue<string> myqueue;
	list<string> lil,lil2;
	list<string>::iterator it,it2,it3;
	
/**** UCS variables ****/
	int *pathID_ucs = new int[count_nodes];						// pathID_ucs[] holds nodeIDs of output path for UCS. And some more temporary variables
	int zz=0;
	ofstream outfile_ucs("uniform-cost.result.txt");					// Create and open UCSoutput.txt into writable format
	string outputName_ucs;									// 'outputName_ucs' to hold output string for UCS
	string stl_push_ucs,stl_pop_ucs,tempParent_ucs;			// some temporary variables
	std::queue<string> open,closed;							// 2 queues implemented: 'open' queue and 'closed' queue
	list<string> lil_ucs,lil2_ucs;							// 2 temporary lists implemented to hold the names of the nodes
	list<int> lil_cost;										// 1 temporary list implemented for holding cost of nodes from the root node
	list<string>::iterator it_ucs,it2_ucs,it3_ucs,swapit3,swapit4,clear_itstring;	// iterators implemented. 'swapit3' and swapit4' to sort node names in 'lil_ucs' list
	list<int>::iterator it4_ucs,swapit1,swapit2,clear_itcost;	// iterators implemented. 'swapit1' and 'swapit2' to sort the costs in 'lil_cost' list.
																// the 'lil2_ucs' list is for keeping the record of all the discovered nodes.
/**** DFS variables ****/
	ofstream outfile_dfs("depth-first.result.txt");					// Create and open DFSoutput.txt into writable format
	string outputName_dfs,stl_push_dfs,stl_pop_dfs,tempParent_dfs;	// 'outputName_dfs' to hold output string for DFS. And other temporary variables
	int tempid_dfs;						
	// pathID_dfs[] holds nodeIDs of output path for DFS. 
	int *pathID_dfs = new int[count_nodes];
	list<string> lil_dfs,lil2_dfs;							// 'lil_dfs' list will include sorted names of nodes in ascending order. 'lil2_dfs' list will contain them in descending order.
	list<string>::iterator it_dfs,it2_dfs;					// iterators for the above 2 lists
	std::stack<string> stack_dfs;							// stack implemented 
	std::queue<string> queue_dfs;							// queue implemented (just in order to pop out the output from root to the goal node and no other purpose)

	if(!infile)
		perror("Can't open the file");
	else{
	
/**** Grabbing node info from input file ****/
			
		while(getline(infile,line)){
            if(line[0] == ' '){
                cout<<"space bhenchod"<<endl;
            }
            else{
			if( (int(line[0])>= 48) && (int(line[0]) <= 57) ) {
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
	}

/**** close tempfile ****/
	tempfile.close();
	
/**** open tempfile in read mode ****/	
	ifstream tempfile2("tempfile.txt");
	
/**** Extract the adj Matrix ****/
	for(int i=0; i<numOfNodes; i++){
		for(int j=0; j<numOfNodes; j++){
			tempfile2>>adjMat[i][j];
		}
	}


/**** BFS Implementation start ****/

	for(int i=0; i<numOfNodes; i++){
		Nodes[i].name = name[i];								// Name of all nodes defined
		Nodes[i].nodeID = i;									// numbered all the nodes accordingly
		Nodes[i].parent = "NULL";
	}
	Nodes[0].parent = "ROOT";


	it = lil.begin();											// initialize iterator 'it'
	it2 = lil2.begin();											// initialize iterator 'it2'
	
	stl_push=name[0];				
	myqueue.push(stl_push);										// push 'Alice' ito 'myqueue' queue

	while(p<=numOfNodes){
			stl_pop = myqueue.front();
			lil2.insert(it2,stl_pop);
			for(int id=0; id<=numOfNodes; id++){
				if(Nodes[id].name==stl_pop){
					tempp=Nodes[id].nodeID;
					break;
				}
			}
			myqueue.pop();
	
		for(int j=tempp;j<=numOfNodes;j++){
			if(adjMat[tempp][j] != 0){
				lil.insert(it,name[j]);
				if(Nodes[j].parent == "NULL"){
					it3 = std::find(lil2.begin(), lil2.end(), name[tempp]);
					if ( it3 != lil2.end() )
					{
						Nodes[j].parent = name[tempp];
					}
				}
			}
		}
		lil.sort();
				
		for(it=lil.begin();it != lil.end();it++){			
			stl_push=*it;
			myqueue.push(stl_push);
		}
		lil.clear();
		if(stl_push == "Noah"){
			goto stop;
		}

		p++;
}

/**** Finl Step of BFS ****/
stop:														

/**** fill the pathID[] with nodeIDs of the output nodes in sequence from root to goal node ****/	
	pathID[0] = destID;
	for(int x=1,k=destID; x <= numOfNodes-1; x++){
		tempParent = Nodes[k].parent;
		for(int j=numOfNodes-1; j >= 0;j--){
			if(tempParent == Nodes[j].name){
				k = j;
				q++;
				pathID[q]=k;
				break;
			}
		}
	}

/**** Form the output string into BFSoutputName ****/
	for(int i=q; i>=0; i--){
		BFSoutputName += Nodes[pathID[i]].name;
		if(i!=0){
		BFSoutputName += "-";
		}
	}
		
	
	BFSoutfile<<"Breadth"<<endl;
	BFSoutfile << BFSoutputName;													// Write the output of BFS into BFSoutput.txt
	cout<<"******************************"<<endl;
	cout<<"BFS out->"<<BFSoutputName<<endl;		
	cout<<"******************************"<<endl;
	
/**** BFS Implementation end ****/
	
	
/**** UCS Implementation start ****/

	for(int i=0; i<numOfNodes; i++){
		Nodes[i].name = name[i];								// Name of all nodes defined
		Nodes[i].nodeID = i;									// numbered all the nodes accordingly
		Nodes[i].parent = "NULL";
		Nodes[i].cost=0;
	}
	Nodes[0].parent = "ROOT";

	it_ucs = lil_ucs.begin();									// initialize iterator 'it_ucs'
	it2_ucs = lil2_ucs.begin();									// initialize iterator 'it2_ucs'
	it4_ucs = lil_cost.begin();									// initialize iterator 'it_ucs'
	
	stl_push_ucs=Nodes[0].name;									
	open.push(stl_push_ucs);									// Push Alice into 'open' queue
	
	while(!open.empty()){
		
		stl_pop_ucs = open.front();
		lil2_ucs.insert(it2_ucs,stl_pop_ucs);

/**** test if goal ****/
		if(stl_pop_ucs == "Noah"){
			goto stop2;
		}	
		
/**** find its nodeID ****/
		for(int id=0; id<=numOfNodes; id++){
			if(Nodes[id].name==stl_pop_ucs){
				tempp=Nodes[id].nodeID;
				break;
			}
		}

/**** expand kids (if any) ****/
		for(int j=tempp;j<=numOfNodes;j++){
			if(adjMat[tempp][j] != 0){
				lil_ucs.insert(it_ucs,name[j]);
				lil_cost.insert(it4_ucs,adjMat[tempp][j]);
				
				if(Nodes[j].parent == "NULL"){
					it3_ucs = std::find(lil2_ucs.begin(), lil2_ucs.end(), name[tempp]);
					if ( it3_ucs != lil2_ucs.end() )
					{
						Nodes[j].parent = name[tempp];
						Nodes[j].cost=adjMat[tempp][j]+Nodes[tempp].cost;					
					}
				}
				else{
					if(Nodes[j].cost > adjMat[tempp][j]+Nodes[tempp].cost){
						Nodes[j].parent = name[tempp];
						Nodes[j].cost=adjMat[tempp][j]+Nodes[tempp].cost;										
					}
				}
			}
		}

/**** sort them ****/
	
	/*for(int ii=0; ii<= lil_cost.size(); ii++){
		for(swapit1 = lil_cost.begin(),
			swapit2 = lil_cost.begin(),
			swapit2++,
			swapit3 = lil_ucs.begin(),
			swapit4 = lil_ucs.begin(),
			swapit4++;
			swapit2 != lil_cost.end();
			swapit1++,swapit2++,swapit3++,swapit4++
			){
			// sort according to cost!
			if(*swapit1 > *swapit2){
				swap(*swapit1,*swapit2);
				swap(*swapit3,*swapit4);
			}
			// if costs of both nodes are same, sort them by name!
			if(*swapit1 = *swapit2){
			if(*swapit3 < *swapit4)
				swap(*swapit3,*swapit4);
			}
		}
	}*/
	
		for(it_ucs=lil_ucs.begin();it_ucs != lil_ucs.end();it_ucs++){			
			stl_push_ucs=*it_ucs;
			open.push(stl_push_ucs);
		}
// remove the one pushed into open

		clear_itstring=lil_ucs.begin();
		clear_itcost = lil_cost.begin();
		stl_push_ucs=*clear_itstring;
		
		lil_ucs.remove(*clear_itstring);		
		lil_cost.remove(*clear_itcost);		

		closed.push(stl_push_ucs);
		//cout<<"PUSHEDintoCLOSED-->"<<stl_pop_ucs<<endl;
		open.pop();
//		cout<<stl_pop_ucs<<endl;
	}	

stop2:
	
	q=0;
	pathID_ucs[0] = destID;
	for(int x=1,k=destID; x <= numOfNodes-1; x++){
		tempParent_ucs = Nodes[k].parent;
		for(int j=numOfNodes-1; j >= 0;j--){
			if(tempParent_ucs == Nodes[j].name){
				k = j;
				q++;
				pathID_ucs[q]=k;
				break;
			}
		}
	}

	for(int i=q; i>=0; i--){
		outputName_ucs += Nodes[pathID_ucs[i]].name;
		if(i!=0){
		outputName_ucs += "-";
		}
	}
		

	for(int cc=0; cc<=numOfNodes; cc++){
	//	cout<<Nodes[cc].name<<"->"<<Nodes[cc].cost<<endl;
	}
	
	for(int cc=0; cc<=numOfNodes; cc++){
	//	cout<<Nodes[cc].name<<"->"<<Nodes[cc].parent<<endl;
	}
	
	
	outfile_ucs<<"Uniform-Cost"<<endl;
	outfile_ucs << outputName_ucs;
	cout<<"******************************"<<endl;
	cout<<"UCS out->"<<outputName_ucs<<endl;		
	cout<<"******************************"<<endl;

/**** UCS Implementation end ****/


/**** DFS Implementation start ****/

	for(int i=0; i<numOfNodes; i++){
		Nodes[i].name = name[i];								// Name of all nodes defined
		Nodes[i].nodeID = i;									// numbered all the nodes accordingly
		Nodes[i].discovered = "NULL";
		Nodes[i].explored = "NULL";
		Nodes[i].parent = "NULL";
	}
	Nodes[0].discovered = "!NULL";

	it_dfs = lil_dfs.begin();				// initialize iterator

	stl_push_dfs=name[0];
	stack_dfs.push(stl_push_dfs);	
	it_dfs = lil_dfs.begin();								// initialize iterator

	while(!stack_dfs.empty()){

		stl_pop_dfs = stack_dfs.top();
		queue_dfs.push(stl_pop_dfs);
		stack_dfs.pop();


		if(stl_pop_dfs == "Noah"){
			goto stop3;
		}

// find its nodeID
		for(int id=0; id<=numOfNodes; id++){
			if(Nodes[id].name==stl_pop_dfs){
				tempid_dfs=Nodes[id].nodeID;
				break;
			}
		}
// explored
		if(Nodes[tempid_dfs].explored == "NULL"){				// if undiscovered!
			//Nodes[tempid_dfs].discovered = "!NULL";
			Nodes[tempid_dfs].explored = "!NULL";

// expand kids
			for(int j=0;j<=numOfNodes;j++){
				if(adjMat[tempid_dfs][j] != 0){

// checkpoint
					if(Nodes[j].explored == "NULL"){
						lil_dfs.insert(it_dfs,name[j]);
						Nodes[j].discovered = "!NULL";
						Nodes[j].parent = Nodes[tempid_dfs].name;
					}
				}
			}

// sort the list 
			lil_dfs.sort();	
			for(it_dfs=lil_dfs.begin(),it2_dfs = lil2_dfs.begin();it_dfs != lil_dfs.end();it_dfs++){			
				stl_push_dfs=*it_dfs;
				lil2_dfs.insert(it2_dfs,stl_push_dfs);
				it2_dfs--;
			}
			
// & push into the stack
			for(it2_dfs=lil2_dfs.begin();it2_dfs != lil2_dfs.end();it2_dfs++){			
				stl_push_dfs=*it2_dfs;				
				stack_dfs.push(stl_push_dfs);
			}			
			lil_dfs.clear();
			lil2_dfs.clear();
		}				
	}

stop3:
	
	q=0;
	pathID_dfs[0] = destID;
	for(int x=1,k=destID; x <= numOfNodes-1; x++){
		tempParent_dfs = Nodes[k].parent;
		for(int j=numOfNodes-1; j >= 0;j--){
			if(tempParent_dfs == Nodes[j].name){
				k = j;
				q++;
				pathID_dfs[q]=k;
				break;
			}
		}
	}
	
	for(int i=q; i>=0; i--){
		outputName_dfs += Nodes[pathID_dfs[i]].name;
		if(i!=0){
			outputName_dfs += "-";
		}
	}

	outfile_dfs<<"Depth"<<endl;
	outfile_dfs << outputName_dfs;
	cout<<"******************************"<<endl;
	cout<<"DFS out->"<<outputName_dfs<<endl;		
	cout<<"******************************"<<endl;

/**** DFS Implementation end ****/

	BFSoutfile.close();
	outfile_ucs.close();
	outfile_dfs.close();
	infile.close();	
	return 0;
}
