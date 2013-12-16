#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

typedef struct node {
    int lo;
	int hi;
	bool is_overlap;
	node *left;
	node *right;	
	node(int low, int high): lo(low), hi(high), is_overlap(false), left(NULL), right(NULL) {}
}node;

class Merge_Overlapping_Ranges {
private:
	node *root;

public:
	Merge_Overlapping_Ranges(): root(NULL) {}

	// O(log n)
	void insert(pair<int,int> &p) {
		if(!root) {
			root = new node(p.first, p.second);
		}
		else {
			node *parent = NULL;
			
			if(!query_interval(p, &parent)) {
				int low = p.first;
				int high = p.second;
				
				node *tmp = new node(low, high);

				if(low < parent->lo) {
					parent->left = tmp;
				}	
				else if(low > parent->lo) {
					parent->right = tmp;
				}
			}
		}
	}

	bool is_interval_overlap(int low, int high, node **parent) {
		node *tmp = root;
		node *prev = NULL;
		
		while(tmp) {
			prev = tmp;
						
			if((low >= tmp->lo && low <= tmp->hi) || (high >= tmp->lo && high <= tmp->hi)) {
				tmp->is_overlap = true;
				return true;
			}
			else if(low < tmp->lo) {
				tmp = tmp->left;
			}
			else if(low > tmp->lo) {
				tmp = tmp->right;			
			}
		}

		*parent = prev;
		return false;
	}

	bool query_interval(pair<int,int> &p, node **parent) {
		if(is_interval_overlap(p.first, p.second, parent)) {
			return true;
		}

		return false;
	}
	
	vector<pair<int,int>> get_non_overlapping_ranges() {
		vector<pair<int,int>> vec;
		stack<node*> s;
		
		s.push(root);

		while(!s.empty()) {
			node *tmp = s.top();
			s.pop();

			if(!tmp->is_overlap) {
				vec.push_back(make_pair(tmp->lo, tmp->hi));	
			}
			
			if(tmp->right) {
				s.push(tmp->right);
			}
			if(tmp->left) {
				s.push(tmp->left);
			}	
		}	
		
		return vec;
	}
};

int main() {
	// your code goes here

	Merge_Overlapping_Ranges m;
	vector<pair<int,int>> vec = {{1,2}, {3,4}, {3,6}, {8,10}};
	
	// O(n log n)
	for(int i = 0; i < vec.size(); i++) {
		m.insert(vec[i]);	
	}
	// O (n)
	vec = m.get_non_overlapping_ranges();
	
	for_each(vec.begin(), vec.end(), [](pair<int,int> p) { cout << p.first << ", " << p.second << endl; });

	return 0;
}