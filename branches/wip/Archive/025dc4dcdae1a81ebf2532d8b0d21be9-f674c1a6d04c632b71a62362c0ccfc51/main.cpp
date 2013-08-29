
struct NonTrivial {
    
    NonTrivial ( int arf ) {
        
    }
};

int main () {
    NonTrivial* nt = new NonTrivial[ 500 ];
}