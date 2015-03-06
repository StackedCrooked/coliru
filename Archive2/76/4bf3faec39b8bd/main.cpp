#include <fstream>

using namespace std;

int main() {
    int const N = 10;
    int const C= 2;
    
    char *c ="(";
    char *c_1 =",";
    char *c_2 =")";
    
    int array[N][C];
    ifstream file;
    file.open("file.txt");
    int index = 0;
    int index2 = 0;
    
    // if((first_char == '(') && (second_char == ',') && (third_char == ')'))
    if(!file.eof)
    {
    
    
       for(index ; index  < N; index ++){
           for(index2;index2 < C; index2++){
                  file >>array[index ][index2];
          }} // this where the nested loop end 
    }
}