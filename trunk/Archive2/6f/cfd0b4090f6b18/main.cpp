#include <iostream>


class asdf
{
    public:
		static const asdf staticAsdf;
        
        int x;
        
    	asdf();
		asdf(int x);
    	asdf(const asdf& myAsdf);
};


const asdf asdf::staticAsdf(5);

int x;

asdf::asdf()
{
    std::cout << "empty contructor" << std::endl;
}
asdf::asdf(int x)
{
	std::cout << "int contructor " << x << std::endl;
    this->x = x;
}

asdf::asdf(const asdf& myAsdf)
{
    std::cout << "copy contructor" << std::endl;
    this->x = myAsdf.x;
}


int main()
{
    asdf i = asdf::staticAsdf;
    std::cout << i.x << std::endl;
}
