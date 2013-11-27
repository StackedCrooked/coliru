
#include <iostream>
#include <string>

using namespace std;

class Contacts {
  private:
    string Surname, Firstname, Address, PhNo;
  public:
    void storeName (string,string);
    void storeAddress (string); 
    void storePhNo (string);
    string getInfo();
};

void Contacts::storeName (string storeSurname, string storeFirstname) {
    
  Surname = storeSurname;
  Firstname = storeFirstname;
}

void Contacts::storeAddress (string storeaddress){

    Address = storeaddress;
}

void Contacts::storePhNo (string storephno){

    PhNo=storephno;
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


cout<< test.getInfo();

}