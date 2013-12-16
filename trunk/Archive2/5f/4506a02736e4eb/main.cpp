#include <memory>

struct Coord3{
    float x,y,z;
    void setPos(float tx,float ty,float tz){
        x=tx;y=ty;z=tz;}
};

class Item{
  private:
    int itemID,Str,Dex,Int;
    Coord3 pos;
  public:
    int getItemID(){return itemID;}
    int getStr(){return Str;}
    Coord3 getPos(){return pos;}
    //added this so it compiles:
    void doSomethingElse() const {}
};

class SimpleChar{
  private:
    int level;
    float health;
    std::shared_ptr<Item> inventory[20];
  public:
    std::shared_ptr<Item> getInventory(int i){return inventory[i];};
};

#include <iostream>

int main(){
    SimpleChar *myChar= new SimpleChar; //changed that so it compiles
    
    if(myChar->getInventory(0).get()!=NULL){
        myChar->getInventory(0)->getPos().setPos(0,0,0);
        std::cout<<myChar->getInventory(0)->getStr()<<std::endl;
            myChar->getInventory(0)->doSomethingElse();
    }
}