#include <iostream>
#include <cstdlib>
#include <vector>
#include <deque>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <set>
#include <limits>
#include <utility>
#include <list>


using namespace std;

const int max_weight = numeric_limits<int>::infinity();

inline int map_letter_to_int(char ch)
{
    //map digit d to letter c
    int asci_a = toupper(ch)-65;
    return asci_a;
}


class hexGraph{
    public:
		hexGraph(int board_size){
			int count=0;
			size = board_size;
			edgelist.resize(size*size);
			node_mark.resize(size*size);
			for(int i=0; i< size; ++i){
				for(int j =0; j < size; ++j){
					makeNode(i,j, edgelist[count]);
					node_mark[count] = '.'; //static_cast<char>(46+i);
					count++;
				}
			}
		}

		int node_number_from_ij(int i, int j) { return i*size+j; }

		void get_ij_from_node_pos(int &i, int &j, int pos){
			i = pos / size;
			j = pos % size;
			return;
		}

		void makeNode(int i, int j, deque< int > &elist){
			if((i==0 && j==0)){ // 2 edges node TOP
				elist.push_front(i*size+j+1);
				elist.push_front((i+1)*size+j);
			}else if (i== (size-1) && j == (size-1)){   // 2 edges nodes BOTTOM
				elist.push_front(i*size+j-1);
				elist.push_front((i-1)*size+j);
			}else if((i==0 && j == (size-1))){ // 3 edges nodes
				elist.push_front(i*size+j+1);
				elist.push_front((i-1)*size+j);
				elist.push_front((i-1)*size+j-1);
			}else if((i==(size-1) && j == 0)){ // 3 edges nodes
				elist.push_front(i*size+j-1);
				elist.push_front((i+1)*size+j);
				elist.push_front((i+1)*size+j+1);
			}else if( (i>0 && i < (size-1))  && (j == 0 || j == (size -1))){ // 4 edges nodes
				elist.push_front(i*size+j+1);
				elist.push_front(i*size+j-1);
				elist.push_front((i+1)*size+j);
				elist.push_front((i+1)*size+j+1);
			}else if(((i==0 || i==(size-1)) && (j > 0  && j < (size-1)))){ // 4 edges nodes
				elist.push_front(i*size+j+1);
				elist.push_front(i*size+j-1);
				elist.push_front((i-1)*size+j);
				elist.push_front((i-1)*size+j-1);
			}else{ // 6 edges nodes
				elist.push_front(i*size+j+1);
				elist.push_front(i*size+j-1);
				elist.push_front((i+1)*size+j);
				elist.push_front((i+1)*size+j+1);
				elist.push_front((i-1)*size+j);
				elist.push_front((i-1)*size+j-1);
			}
		}

		void print(){
			int count=0,k=0;

			for(k=0; k < size; ++k) cout << " ";
			cout << "NORTH" << endl;
			cout << "   ";
			for(int i=0; i< size; ++i) cout << static_cast<char>(65 + i) << " ";
			cout << endl;
			for(int i=0; i< size; ++i){
				k=0;
				if(i == (size/2)){
				       	cout << "WEST";
					k=4;
				}
				for(; k <= i; ++k) cout << " ";
				cout <<setw(2)<< i+1;
				for(int j=0; j< size; ++j){
					cout << " " << node_mark[count++];
				}
				if(i == (size/2)) cout << "   EAST   ";
				cout << endl;
			}
			for(k=0; k < size; ++k) cout << " ";
			cout << "    SOUTH" << endl;
		}

		int get_size(){ return size;}

		int set_node_mark(int pos, char ch, int verbose){ 
			if(node_mark[pos] == '.') node_mark[pos] = ch;
			else{
				if(verbose) cout << "Already marked position" << endl;
				return 0;
			}
			return 1;
		}

		char get_node_mark(int pos) { return node_mark[pos]; }

		void automatic_mark(char ch){
			int i, j, ans;
			do{
				i = (rand() % 10) + 1;
				j = (rand() % 10) + 1;
				ans = set_node_mark(node_number_from_ij(j,i), ch, 0);
			}while(ans==0);
		}

		vector< deque < int > >get_edge_list(){return edgelist;}

	protected:
		int size;
		vector< deque < int > > edgelist;
		vector < char > node_mark;
};


static int check_input_location(string location, int &i, int &j, hexGraph hex_graph)
{
	int pos1, pos2;

	if(location.size() > 3){
		cout << "Please enter a valid location" << endl;
		return 0;
	}

	pos1 = map_letter_to_int(location[0]);
	if(pos1 < 0 || pos1 > hex_graph.get_size()-1){
		cout << "Please enter a valid location" << endl;
		return 0;
	}
	
	if(!isdigit(location[1]) || (location.size() == 3 && !isdigit(location[2]))){
		cout << "Please enter a valid location" << endl;
		return 0;
	}
	pos2 = atoi(&location[1]);
	if(pos2 < 1 && pos2 > hex_graph.get_size()){
		cout << "Please enter a valid location" << endl;
		return 0;
	}
	pos2--;
	i = pos1;
	j = pos2;
	return 1;
}

static void DijkstraComputePaths(int source, hexGraph hex_graph,
                          vector<int> &min_distance, vector<int> &previous)
{
	int n = hex_graph.get_size();
	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	set<pair<int, int> > vertex_queue;
	vertex_queue.insert(make_pair(min_distance[source], source));

	while (!vertex_queue.empty()) 
	{
		int dist = vertex_queue.begin()->first;
		int u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());

		// Visit each edge exiting u
		const deque<int> neighbors = hex_graph.get_edge_list()[u];
		for (deque<int>::const_iterator neighbor_iter = neighbors.begin();
				neighbor_iter != neighbors.end();
				neighbor_iter++)
		{
			int v = *neighbor_iter;
			int weight = 1;
			int distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v]) {
				vertex_queue.erase(make_pair(min_distance[v], v));
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(make_pair(min_distance[v], v));
			}

		}
	}
}

list<int> DijkstraGetShortestPathTo( int vertex, const vector<int> &previous)
{
	list<int> path;
	for ( ; vertex != -1; vertex = previous[vertex])
		path.push_front(vertex);
	return path;
}


static int is_game_ended(hexGraph hex_graph, const vector<int> &previous)
{
	int ans = 1;
	list<int> path = DijkstraGetShortestPathTo(1, previous);
	for(list<int>::iterator it=path.begin(); it != path.end(); ++it){
		//if(hex_graph.get_node_mark(*it) == 'X')
	}
	return ans;
}

int main()
{
	int board_size, i, j;
	char p_again='Y';
	string location;
	vector<int> min_distance;
	vector<int> previous;

	srand(time(0));
	cout << "Application start..." << endl;
	cout <<"---------------------------"<< endl;
	cout <<"Enter number of hexes (>5) on 1 side: " << endl;
	cin >> board_size;
	cout <<"---------------------------"<< endl;
	if(board_size < 6){
		cout << "Board is too small. Program exits" << endl;
		return 1;
	}


	//system("cls");
	cout <<"***********************************************************"<< endl;
	cout <<"*ITEM           * SYMBOL  *       NOTES                   *"<< endl;
	cout <<"***********************************************************"<< endl;
	cout <<"*Empty Location *    .    *                               *"<< endl;
	cout <<"*   Human Piece *    X    * connects West-East, moves 1st *"<< endl;
	cout <<"*Computer Piece *    0    * connects North-South          *"<< endl;
	cout <<"***********************************************************"<< endl;

	hexGraph hex_graph(board_size);
	DijkstraComputePaths(0, hex_graph, min_distance, previous);

	while(p_again == 'Y' || p_again == 'y'){
		while(is_game_ended(hex_graph, previous)){
			hex_graph.print();
			cout << "Enter location: " << endl;
			cin >> location;
			if(check_input_location(location, i, j, hex_graph)){
				hex_graph.set_node_mark(hex_graph.node_number_from_ij(j,i), 'X', 1);
				hex_graph.automatic_mark('O');
			}
		}
		cout << "Play again (Y or N)? " << endl;
		cin >> p_again;
	}
	return 1;
}