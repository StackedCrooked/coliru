using MySignature = void(double, int, unsigned int);

typedef void CSignature(double);

MySignature f;

void f(double, int, unsigned int){}

CSignature g;

void g(double){}

int main(){    

}
