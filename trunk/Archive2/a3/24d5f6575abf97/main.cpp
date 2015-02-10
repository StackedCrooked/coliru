#include <iostream>
#include <string>
using namespace std;

struct Node
{
  string data;
  Node *link;
};

class Lilist
{
  public:
    Lilist() {head = NULL;}
    void add(string item);
    void show();
    void move_front_to_back();
    Node* search(string target);

  private:
    Node *head;
};

int main()
{
  Lilist L1, L2;
  string target;

  L1.add("Charlie"); //add puts a name at the end of the list
  L1.add("Lisa");
  L1.add("Drew");
  L1.add("Derrick");
  L1.add("AJ");
  L1.add("Bojian");

  cout << "Now showing list One:\n";
  L1.show(); // displays the list (This function displayed the list properly)
  cout << std::endl;

  L1.move_front_to_back();
  L1.show();
  cout << std::endl;
  L1.move_front_to_back();
  L1.show();
  cout << std::endl;

  return(0);
}


void Lilist::add(string item)
{
  Node *temp;
  if(head == NULL)
  {
    head = new Node;
    head -> data = item;
    head -> link = NULL;
  }
  else
  {
    for(temp = head; temp -> link != NULL; temp = temp -> link)
        ;
    temp -> link = new Node;
    temp = temp -> link;
    temp -> data = item;
    temp -> link = NULL;
  }
}

void Lilist::show()
{
  for(Node *temp = head; temp != NULL; temp = temp -> link)
    std::cout << temp -> data << " ";
}

void Lilist::move_front_to_back()
{
  Node *temp;
  Node *tail;

  temp = head;

  for(tail = head; tail->link != NULL; tail = tail -> link)
    ;

  head = head -> link;
  tail -> link = temp;
  temp -> link = NULL;
}