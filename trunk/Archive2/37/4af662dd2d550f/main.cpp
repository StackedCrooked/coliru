#include <iostream>
using namespace std;
 
const int MAX_SIZE = 30;
template <typename T>
class Stack
{
private:
struct Node
{
Node *head;
Node *tail;
Node *curr;
int num_items;
T data;
Node *link;
};
 
Node *top;
Node *curr;
int num_items;
 
public:
 
Stack()
{
top = NULL;
curr = NULL;
num_items = 0;
}
 
Stack(const Stack& s)
{
*this = s;
}
 
 
Stack& operator=( const Stack& rhs ){
  // call this->clear() to avoid memory leak
  if( rhs.top == NULL ){ top = NULL; return *this; }
  Node** store = &top;
  for( Node* curr = rhs.top; curr != NULL; curr = curr->link ){
    Node* newNode = new Node;
    num_items++;
    newNode->data = curr->data;
    *store = newNode;
    store = &newNode->link;
  }
  return *this;
}
 
 
void Push(T item)
{
if(num_items != MAX_SIZE)
{
Node *p = new Node;
p -> data = item;
p->link = top;
top = p;
num_items++;
}
}
 
// navigates to the end of the list
// the end of the list does not necessarily correspond to its maximum size; it's just at the last existing element
T Pop()
{
Node* temp = top;
if(IsEmpty())
{
return NULL;
}
top = temp->link;
num_items--;
return temp->data;
}
 
 
T Peek()
{
if(IsEmpty())
{
return -1;
}
return top->data;
}
 
bool IsEmpty()
{
return top == NULL;
}
 
bool IsFull()
{
return num_items == MAX_SIZE;
}
int Size()
{
return num_items;
}
 
 
Stack operator+(const Stack& s) const
{
// copy the first list
Stack t = *this;
Stack u = *this;
Node *n = s.top;
 
// iterate through the second list and copy each element to the new list
while (n != NULL && !t.IsFull())
{
t.Push(n->data);
n = n->link;
}

n = t.top;
while (n != NULL && !t.IsEmpty())
{
u.Push(n->data);
t.Pop();
n = t.top;
}
 
return u;
}
 
// returns if two lists are equal (by value)
bool operator==(const Stack& s) const
{
// the lists are not equal if they're of different sizes
if (num_items != s.num_items)
return false;
 
Node *p = top;
Node *q = s.top;
 
// iterate through each list
while (p != NULL)
{
// if any pair of elements differ, the lists are not equal
if (p->data != q->data)
return false;
p = p->link;
q = q->link;
}
 
return true;
}
 
// returns if two lists are not equal (by value)
bool operator!=(const Stack& s) const
{
return !(*this == s);
}
 
// returns a string representation of the entire list (e.g., 1 2 3 4 5)
// the string "NULL" should be returned for an empty list
friend ostream& operator<<(ostream& out, const Stack &s)
{
// "NULL" if the list is empty
if (s.top == NULL)
out << "NULL";
else
{
Node *n = s.top;
 
// otherwise iterate through the list and display each element separated by a space
while (n != NULL)
{
out << n->data << " ";
n = n->link;
}
}
 
return out;
}
};
 
/*****************************************
 * YOU MAY NOT CHANGE ANYTHING BELOW THIS!
 *****************************************/
int main()
{
Stack<int> s1;
 
for (int i=0; i<100; i++) // push 1000 times with i+100
s1.Push(i+100);
 
for (int i=0; i<10; i++) // pop 10 times
s1.Pop();
 
for (int i=0; i<1000; i++) // pop 1000 times
s1.Pop();
 
for (int i=0; i<10; i++) // push 10 times with i*i
s1.Push(i*i);
 
Stack<int> s2(s1); // s2 declared as a copy of s1
 
Stack<int> s3;
s3 = s3 + s2;
cout << "*declare s3 as a copy of s2 (stack s3 = s2)\ns3=" << s3 << endl; // copy constructor (=)
cout << "s3.Size()=" << s3.Size() << endl;
cout << "s3.IsEmpty()=" << ((s3.IsEmpty()) ? "T" : "F") << endl;
cout << "s3.IsFull()=" << ((s3.IsFull()) ? "T" : "F") << endl;
cout << "s3.Peek()=" << s3.Peek() << endl;
cout << endl;
 
return 0;
}
 