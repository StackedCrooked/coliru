#include <memory>
#include <iostream>

class Object
{
public:
    Object() :ownId(id++){
		std::cout << "Object() id = " << ownId << std::endl;
	}
	~Object(){
		std::cout << "~Object() id = " << ownId << std::endl;
	}
private:
	int ownId;
	static int id;
};
int Object::id = 0;

int main(int, char*[])
{
	std::unique_ptr<Object> x = std::make_unique<Object>();
	std::unique_ptr<Object[]> y = std::make_unique<Object[]>(10);
	return 0;
}