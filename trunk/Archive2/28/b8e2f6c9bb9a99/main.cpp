class Node {
    friend class List; // friends can touch each other's private parts
  private:
    Node *next;
};

class List {
  public:
    void example() const {
        Node n;
        n.next = nullptr; // edit Node's private data member
    }
};

int main() {
    List lst;
    lst.example();
}