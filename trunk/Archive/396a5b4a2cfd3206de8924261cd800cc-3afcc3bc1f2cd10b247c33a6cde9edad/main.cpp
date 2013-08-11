struct Node {
    Node(Node *n) : next{n} {}
    Node *getNext() {return next;}
    Node *next;
};

struct List {
    List();
    ~List();
    
    Node *first, *last;
    int nodeListTotal;
};

List::List():first(nullptr), last(nullptr), nodeListTotal(0)
{
}    

List::~List()
{
    Node* currentNode = first;

    while( currentNode != 0 ) 
    {
        Node* temp = currentNode->getNext();
        delete currentNode;
        currentNode = temp;
    }

    first = 0;
}

int main() {
    List list;   
}