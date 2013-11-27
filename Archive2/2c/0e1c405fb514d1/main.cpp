
#include <iostream>
#include <string>

using namespace std;

class Contacts {
  private:
    string Surname, Firstname, Address, PhNo;
  public:
    void storeName (string,string);
    void storeAddress (string storeaddress) {Address = storeaddress;}
    void storePhNo (string storephno) {PhNo=storephno;}
    string getName();
    string getAddress();
    string getPhNo();
    string getInfo();
};

void Contacts::storeName (string storeSurname, string storeFirstname) {
    
  Surname = storeSurname;
  Firstname = storeFirstname;
}


string Contacts::getName (){

string temp;
temp = Firstname;
temp += "  ";
temp += Surname;

return temp;
}

string Contacts::getAddress(){

string temp;
temp = Address;
return temp;
}

string Contacts::getPhNo(){

string temp;
temp = PhNo;
return temp;

}

string Contacts::getInfo (){
    string temp;
    temp = Firstname;
    temp += " ";
    temp += Surname;
    temp += "\n";
    temp += Address;
    temp += "\n";
    temp += PhNo;
    
    return temp;

}

class AddressBook{
     public:
    Contacts People[100];
    int NoPeople;
   
    void printAddressBook();

};

void AddressBook::printAddressBook(){
    
    for(int i=0; i<NoPeople; i++){
    cout << People[i].getInfo() << endl;
    }
}

int main(){

AddressBook test;    

test.NoPeople = 2;

test.People[0].storeName("Ann", "Southall");
test.People[0].storeAddress("12 Park st");
test.People[0].storePhNo("0427854623");

test.People[1].storeName("Lawoko","Lars");
test.People[1].storeAddress("26 Wilpena Place, Vermont South, Melbourne");
test.People[1].storePhNo("0400510502");

test.printAddressBook();
}