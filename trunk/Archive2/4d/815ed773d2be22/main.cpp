#include <iostream>

using namespace std;

struct list {
    int data;
    list* next;
};

void insert_back(list* &first, int data);
void print(list* first);

int main() {
    list* first = NULL;
    int i;
    do {
        cout<<"Inserisci un numero da aggiungere alla lista, metti una lettere per terminare: ";
        if((cin>>i).good())
            insert_back(first, i);
    }while(cin.good());

    cout<<"Lista inserita: n";
    print(first);

    return 0;
}

void insert_back(list* &first, int data) {
    list* n = new list;
    n->data = data;
    n->next = NULL;

    if(first == NULL) {
        first = n;
  }else {
        list* app = first;
        while(app->next != NULL)
            app = app->next;

        app->next = n;
    }
}

void print(list* first) {
    list* n = first;
    while(n != NULL) {
        cout<<n->data<< " ";
        n = n->next;
    }
}
