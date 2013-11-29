struct Coord3{
    float x, y, z;

    Coord3() {x=0;y=0;z=0;};///Is this Correct?
};

struct Stat{
    int Str,Dex,Int;

    Stat(){Str=0;Dex=0;Int=0;};
};

struct Item{
    Stat myStats;

    Item(){};
};

class SimpleChar{
    Coord3 pos;
    Stat myStats;
    int level;
    float health;
    Item inventory[20];

    SimpleChar(){
    level=0;
    health=100;
    };///What happens with 'pos', 'inventory' and 'myStats' in this class's constructor?
};

int main(){
    SimpleChar myChar;
    if(myChar.inventory[0].get()!=NULL){...}///this caused the most recent SEGFAULT as mentioned below. Why wouldn't this work?
}