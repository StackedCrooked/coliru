#include <iostream>
#include <string>

struct Qnode {
    std::string val;    
    Qnode *next;
};

struct Queue {
    Qnode *first;
    Qnode *last;
};

struct PQnode {
    int priority;
    Queue q;
    PQnode *next;
};

typedef PQnode *PQ;

int sizePQ (const PQ& pq) {
    int temp =0;
	PQnode* p = pq;
	while (p != NULL)
	{
		Qnode* derp = p->q.first;;
		while (derp != NULL)
		{
			temp++;
			derp = derp->next;
		}
		p = p->next;
	}
    return temp;
}

int main() {
    Qnode q1 = {"a", 0};
    Qnode q2 = {"b", &q1};
    
    Queue q = {&q2, &q1};
    PQnode pq = {0, q, 0};
    
    std::cout << sizePQ(&pq);
}