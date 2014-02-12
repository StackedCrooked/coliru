using namespace std;

class Pages{
    
          public:
                int m;
};

class Books{

        public:
                Pages Physics(int i){cout << "Number of pages" <<  i << endl;
                                      Pages b;  
                                        b.m = i+1;
                                      return b;  
    
                                        }   
};

int main(){

        Books b1; 
        //cout << b1.Physics(10);
        Pages p = b1.Physics(10);
        cout << p.m;
    

    
    
        return 0;
}
