#include <iostream>
using namespace std;

template <class E>
class List{

public:

List(){};
virtual ~List(){};
virtual void insert(const E& it) = 0;
virtual void clear() = 0;
virtual void append(const E&it) = 0;
virtual void remove() = 0;
virtual void start() = 0;
virtual void end() = 0;
virtual void next() = 0;
virtual void prev() = 0;
virtual int length() const = 0;
virtual int currentpos() = 0;
virtual void movetoPos(int pos) = 0;
virtual const E& getvalue() const = 0;
};

template<class E>
class Alist : public List<E>{

private:

int maxSize;
int listSize;
int curr;
int biggest;
E* listArray;

public:

Alist(){
    maxSize = 50;
    listSize = 0;
    biggest = 0;
    curr = 0;
    listArray = new E[maxSize];
}

~Alist(){
    delete[] listArray;
}

void clear(){

    delete[] listArray;
    listSize = 0;
    curr = 0;
    listArray = new E[maxSize];
}

void insert(const E& it){
    if (curr <0 || curr >= maxSize){
        cout << "The value is out of bounds.";
        return;
    }

    for (int i = listSize; i >= curr; i--){
        listArray[i] = listArray[i + 1];
    }

    if (curr > biggest)
        biggest = curr;

    listArray[curr] = it;
    listSize++;
}

void append(const E& it){
    if (curr <0 || curr >= maxSize){
        cout << "The value is out of bounds.";
        return;
    }

    curr = listSize;
    listArray[listSize++] = it;
    biggest++;

}

void remove(){

    delete[] listArray;
    listSize--;
}

void start(){
    curr = 0;
}


void end(){
    curr = listSize;
}

void next(){
    curr += 1;
}

void prev(){
    curr -= 1;
}

int length() const{

    return listSize;
}

int currentpos() {

    return curr;
}

void movetoPos(int pos){

    if (pos > 0 || pos < maxSize)
        curr = pos;
    else
        cout << "Invalid position.";
}

const E& getvalue() const{

    return listArray[curr];

}

};


int main(){


Alist<int> A;

// Moving the cursor to starting position
A.start();

cout << "What do you want to insert?" << endl;
int number;
cin >> number;

A.insert(number);


cout << "You have entered " << A.getvalue() << endl;
cout << endl;

cout << "The length of the list now is " << A.length() << endl;

cout << "What do you want to append?" << endl;
cin >> number;

A.append(number);

cout << "You have entered " << A.getvalue() << endl;
cout << endl;
cout << "The length of the list now is " << A.length() << endl;


cout << "What do you want to append?" << endl;
cin >> number;

A.append(number);

cout << "You have entered " << A.getvalue() << endl;
cout << endl;
cout << "The length of the list now is " << A.length() << endl;


cout << "The cursor position is " << A.currentpos() << endl;
cout << "Where do you want to move the cursor to?" << endl;
cin >> number;
A.movetoPos(number);
cout << "The cursor position is " << A.currentpos() << endl;


char choice;
cout << "Do you want to clear the list?";
cin >> choice;

if (choice == 'y'){
    A.clear();
    cout << "List has been cleared" << endl << "The length of the list now is " << A.length() <<   endl;
}


return 0;
}
