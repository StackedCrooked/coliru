    #include <iostream>
    #include <string>
    #include <sstream>
    #include <fstream>

    std::string grid[20]={" "};

    std::string get(int string, int member){
      return grid[string].substr(member,1);
    }
    std::string* getNeighbors(int string, int member){
      std::string neighbors[4];
      neighbors[0]=grid[string-1].substr(member,1);//up
      neighbors[1]=grid[string+1].substr(member,1);//down
      neighbors[2]=grid[string].substr(member-1,1);//left
      neighbors[3]=grid[string].substr(member+1,1);//right
      std::string* p=neighbors;
      return p;//Returns up,down,left,right.
    }
    int main(int argc, char** argv){
      grid[1]="@----^---0";
      grid[2]="abcdefghi0";
      grid[3]="jklmnopqr0";//TODO Change to read of txt*/
      std::string* neighbors;
      for(int i=0;grid[1].length()>i;i++){
        neighbors=getNeighbors(2,1);
        if(neighbors[3]=="-" | neighbors[3]=="^"){
          std::string r=get(1,i);
          (r!="0") ? std::cout<<r:(bool)0;//Dangerous. TODO Unknown symbol handling
          std::cout<<neighbors[3];
        }
      }
    }