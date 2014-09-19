class tile {
  int temp;
public:
  tile(){}
  tile(int t){temp = t;}
};

class world {
  tile wmap[100][100][10];
public:
  world(){
    wmap[50][50][5] = tile(42);
    //code that calls the parametized constructor for tile for each element in the array
  }
};

world newWorld;

int main(int argc, char *argv[]){
  newWorld = world();
}
