#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;



// Passive data node for hash tables.
struct Node {
    string word;
    Node* next;
};

class HashTable {
    public:
        HashTable ();
        HashTable (int K);
    	virtual ~HashTable();
    	void insert (string word);
    	void remove (string word);	    // You implement this!
    	bool lookup (string word) const;
    	void print () const;
    	void report () const;
    	static const int DefaultSize;
    protected : 
	    int getTableSize() const;	    
    private : 
	    vector<Node*> table;
    	// The "hash" function will be defined by each child class, 
    	// each one using a different strategy.  But it needs to be
    	// abstract (aka "pure virtual") in the abstract parent class.
    	virtual int hash (string key) const = 0;
	
};

// Note that insert/lookup are completely defined here (and call hash) even
// tho hash is not defined here.  This is called the Template Method design
// pattern.  The hash function is private, meaning the children can't call
// it.  However, they can *define* it.  In fact, that's the only difference
// between the children classes: they each provide a difference
// implementation of hash!

const int HashTable::DefaultSize = 1000;
HashTable::HashTable() : table(DefaultSize) {}
HashTable::HashTable(int K) : table(K) {}

// The destructor has lots of garbage to clean up!  For each bucket with an
// overflow list, we delete the nodes.
HashTable::~HashTable(){
    for (int i=0; i<getTableSize(); i++) {
	    Node* p = table[i];
    	while (p!=NULL) {
	        Node* temp = p;
	        p = p->next;
	        delete temp;
	    }
    }
}

// Simple accessor function that will be used by children classes to
// implement the hash function.  It's protected as children need to use it
// but not public as external clients do not need to know about it.
// This is the only information about the table that the children classes
// need to know, so we can make the table itself private!
int HashTable::getTableSize() const {
    return (int) table.size();
}

// Use open hashing with unsorted linked list for overflow.
void HashTable::insert(string key) {
    const int slot = hash(key);
    Node* newNode = new Node;
    newNode->word = key;
    newNode->next = table[slot];
    table[slot] = newNode;
}

bool HashTable::lookup (string key) const {
    const int slot = hash(key);
    Node* curNode = table[slot];
    while (curNode != NULL) {
	if (curNode->word == key) {
	    return true;
	}
	curNode = curNode -> next;
    }
    return false;
}

// You implement this!
void HashTable::remove(string key) {
    int index = this->hash(key);
    Node* temp = this->table[index];
    if (!lookup(key)){
        return;
    }
    if (temp->next == NULL){ //one element in bucket case
        if (temp->word == key){
            delete temp;
            this->table.erase (this->table.begin() + index);
        }
        return;
    }
    if (temp->word == key){
        this->table[index] = temp->next;
        delete temp;
        return;
    }
    while (temp->next->word != key){
        temp = temp->next;
    }
    Node* temp2 = temp->next;
    temp->next = temp2->next;
    delete temp2;
}

// To help you debug, if you find it useful.
void HashTable::print() const {
    for (int i=0; i<getTableSize(); i++) {
	if (table[i] != NULL) {
	    Node* p = table[i];
	    while (p != NULL) {
		cout << i << "    " << p->word << endl;
		p = p->next;
	    }
	}
    }
}

// So we can tell how good your hash function is ...
// Do NOT override this function in the version you submit.  We will check!
void HashTable::report () const {
    // K is number of buckets
    const int K = getTableSize();
    // How many overflow elements in each bucket?
    vector<int> stats (K);
    int totalNumEntries = 0;
    int numNonZeros = 0;
    int maxOverflowSize = 0;
    for (int i=0; i<K ; i++) {
	if (table[i] != NULL) {
	    numNonZeros++;
	    int numEntriesInThisBucket = 0;
	    Node* p = table[i];
	    while (p != NULL) {
		p = p->next;
		numEntriesInThisBucket++;
	    }
	    totalNumEntries += numEntriesInThisBucket;
	    if (numEntriesInThisBucket > maxOverflowSize) {
		maxOverflowSize = numEntriesInThisBucket;
	    }
	    stats[i]=numEntriesInThisBucket;
	}
    }
    sort(stats.begin(), stats.end());
    const int numEmptyBuckets = K - numNonZeros;
    const int firstNonZeroBucketIndex = numEmptyBuckets;
    cout << "Number of entries in table: " << totalNumEntries << endl;
    cout << "Total # buckets: " << K << " of which " << numEmptyBuckets 
	<< " (" << 100 * numEmptyBuckets / K << "%)" << " were empty." <<
	endl;
    // We want the avg and median # of elements, but ignoring the empty
    // buckets, on the grounds that if we're looking for a valid word, it
    // doesn't matter how many empty buckets there are, as we'll be hashing
    // to a non-empty bucket and traversing that list.
    // To compute the median, find the index that is half-way between
    // firstNonZeroBucketIndex and K.
    const int median = stats[firstNonZeroBucketIndex + numNonZeros/2];
    const int average = totalNumEntries / numNonZeros;
    cout << "Overflow list length:  Max = " << maxOverflowSize 
	<< "  Median = " << median << "  Average = " << average <<  endl;
}

class SimpleHashTable: public HashTable{
    public:
        SimpleHashTable();
        SimpleHashTable(int K);
        ~SimpleHashTable();
        
    private:
        virtual int hash (string key) const;   
};

SimpleHashTable::SimpleHashTable():HashTable(){}

SimpleHashTable::SimpleHashTable(int K):HashTable(K){}

SimpleHashTable::~SimpleHashTable(){}

int SimpleHashTable::hash(string key) const{
    int sum = 0;
    for (int i = 0; i < key.size(); i++){
        sum+=(int)key.at(i);
    }
    return sum % DefaultSize;
    
}


int main(){
    SimpleHashTable x(1000);
    x.insert("hello");
    x.print();
    x.remove("hello");
    x.remove("hello");
    x.print();
}