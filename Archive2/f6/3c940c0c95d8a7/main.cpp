#include <unordered_map>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
using namespace std;

enum class Relation
{
    LifespanOverlapsWith,
	DiedBeforeBirthOf
};

struct Event
{
	unsigned int person1;
	unsigned int person2;
	Relation relation;
};

struct Node
{
	vector<shared_ptr<Node>> before;
	string event;
	unsigned int nbIncoming;
	Node(string event) : event(event), nbIncoming(0) {}
};

struct Person
{
	shared_ptr<Node> birth;
	shared_ptr<Node> death;
};

vector<shared_ptr<Node>> generateTimeline(const vector<shared_ptr<Node>>& nodes)
{
	vector<shared_ptr<Node>> topologicalOrder;
	for (auto& n : nodes) {
		if (n->nbIncoming == 0) topologicalOrder.push_back(n);
	}

	for (unsigned int i = 0; i < topologicalOrder.size(); ++i) {
		for (auto& link : topologicalOrder[i]->before) {
			if (--link->nbIncoming == 0) {
				topologicalOrder.push_back(link);
			}
		}
	}

	return topologicalOrder;
}

vector<shared_ptr<Node>> buildGraph(const vector<Event>& oralData)
{
	//Maps the person IDs to their nodes in the graph
	unordered_map<unsigned int, Person> map;

	//Link birtsh to deaths for every oral history datum, etc
	for (auto& d : oralData) {

		//Create nodes if they don't exist
		if (map[d.person1].birth == nullptr) {
			map[d.person1].birth = make_shared<Node>("Birth of " + to_string(d.person1));
			map[d.person1].death = make_shared<Node>("Death of " + to_string(d.person1));
			map[d.person1].birth->before.push_back(map[d.person1].death);
			map[d.person1].death->nbIncoming++;
		}
		if (map[d.person2].birth == nullptr) {
			map[d.person2].birth = make_shared<Node>("Birth of " + to_string(d.person2));
			map[d.person2].death = make_shared<Node>("Death of " + to_string(d.person2));
			map[d.person2].birth->before.push_back(map[d.person2].death);
			map[d.person2].death->nbIncoming++;
		}

		if (d.relation == Relation::LifespanOverlapsWith) {
			//Person 1 was born before person 2 died AND
			//Person 2 was born before person 1 died
			map[d.person1].birth->before.push_back(map[d.person2].death);
			map[d.person2].death->nbIncoming++;
			map[d.person2].birth->before.push_back(map[d.person1].death);
			map[d.person1].death->nbIncoming++;
		}
		else if (d.relation == Relation::DiedBeforeBirthOf) {
			map[d.person1].death->before.push_back(map[d.person2].birth);
			map[d.person2].birth->nbIncoming++;
		}
	}

	//Collect all the graph nodes in one collection
	vector<shared_ptr<Node>> nodes;
	for (auto& p : map) {
		if (p.second.birth) nodes.push_back(p.second.birth);
		if (p.second.death) nodes.push_back(p.second.death);
	}

	return nodes;
}

void analyzeInformation(const vector<Event>& oralData)
{
	//Build the graph from the oral history data
	vector<shared_ptr<Node>> graphNodes = buildGraph(oralData);

	//Put nodes in topological order
	vector<shared_ptr<Node>> topologicalOrder = generateTimeline(graphNodes);

	//Output result
	if (graphNodes.size() != topologicalOrder.size()) {
		cout << "Data is not internally consistent" << endl;
		return;
	} 

	cout << "Data is internally consistent. Tentative timeline: " << endl;
	for (auto& n : topologicalOrder) {
		cout << n->event << ", ";
	}
}


int main()
{
	vector<Event> v = {
			{1, 2, Relation::DiedBeforeBirthOf},
			{2, 3, Relation::DiedBeforeBirthOf },
			{3, 4, Relation::DiedBeforeBirthOf },
			{ 4, 5, Relation::LifespanOverlapsWith },
			{ 3, 5, Relation::DiedBeforeBirthOf }
	};

	analyzeInformation(v);
    
    return 0;
}