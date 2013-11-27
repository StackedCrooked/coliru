
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



int main(){

Contacts test;

test.storeName("Lawoko", "Lars");
test.storeAddress("26 Wilpena pl");
test.storePhNo("0427854623");

cout<< test.getName() << endl << test.getAddress() << endl << test.getPhNo() << endl;

}