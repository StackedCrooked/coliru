#include <iostream>
#include <memory>
#include <vector>

class Shape
{
public:
    virtual void Draw() = 0;
};


class Square : public Shape
{
public:
	virtual void Draw()
	{
		std::cout << "\nDrawing a square.....\n";
	}

};

class Circle : public Shape
{

public:
	virtual void Draw()
	{
		std::cout << "\nDrawing a cirlce.....\n";
	}
};


int main()
{
	typedef std::unique_ptr<Shape> ShapePointer;
	ShapePointer pSquare = std::make_unique<Square>();
	ShapePointer pCircle = std::make_unique<Circle>();

	std::vector<ShapePointer> list;

	list.emplace_back(std::move(pSquare));
	list.emplace_back(std::move(pCircle));
	
	for (ShapePointer& it : list)
	{
		it->Draw();
	}

	return 0;
}
