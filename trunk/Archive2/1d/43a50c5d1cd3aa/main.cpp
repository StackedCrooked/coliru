#include <iostream>
#include <string>

class Product {
    std::string name;
    float weight;
protected:
	int price;
	bool isExpired;
public:
	Product(const std::string & = "", const float = 0, const int = 0, const bool = false);
	const std::string & getName() const;
	float getWeight() const;
	int getPrice() const;
	bool getExpired() const;

	void setExpired();
};

struct Cookies : public Product {
	Cookies(const std::string &, const float, const int, const bool);
	void setExpired();
};

struct Biscuits : public Product {
	Biscuits(const std::string &, const float, const int, const bool);
	void setExpired();
};

class Cart {
	Product items[6];
	int size;
public:
	Cart();
	void addProduct(const Product & product);
	float getTotalWeight() const;
	int getTotalPrice() const;
	friend std::ostream & operator<<(std::ostream &, const Cart &);
};

Product::Product(const std::string & name, const float weight, const int price, const bool isExpired)
		: name(name), weight(weight), price(price), isExpired(isExpired)
{}

const std::string & Product::getName() const {
	return name;
}
float Product::getWeight() const {
	return weight;
}
int Product::getPrice() const {
	return price;
}
bool Product::getExpired() const {
	return isExpired;
}

void Product::setExpired() {
	isExpired = true;
}

Cookies::Cookies(const std::string & name, const float weight, const int price, const bool isExpired = false)
		: Product(name, weight, price, isExpired)
{}

void Cookies::setExpired() {
	if (!isExpired) {
		isExpired = true;
		price = price * 0.75;
	}
}

Biscuits::Biscuits(const std::string & name, const float weight, const int price, const bool isExpired = false)
		: Product(name, weight, price, isExpired)
{}

void Biscuits::setExpired() {
	if (!isExpired) {
		isExpired = true;
		price = price * 0.5;
	}
}

Cart::Cart() : size(0) {}

void Cart::addProduct(const Product & product) {
	if (size < 6) {
		items[size] = product;
		++size;
	}
}

int Cart::getTotalPrice() const {
	int totalPrice = 0;
	for (int i = 0; i < size; ++i) {
		totalPrice += items[i].getPrice();
	}
	return totalPrice;
}

float Cart::getTotalWeight() const {
	float totalWeight = 0;
	for (int i = 0; i < size; ++i) {
		totalWeight += items[i].getWeight();
	}
	return totalWeight;
}

std::ostream & operator<<(std::ostream & out, const Cart & cart) {
    out << "shooping cart: ";
    for (int i = 0; i < cart.size -1; ++i) {
		out << cart.items[i].getName() << ", ";
	}
    out << cart.items[cart.size-1].getName();
    
	out << "; price: " << cart.getTotalPrice();
    out << "; weight: " << cart.getTotalWeight();
	return out;
}

int main() {
	Cart kruemelCart;
	kruemelCart.addProduct(Cookies("Maxi Soft-Kekse", 0.5, 3));
	kruemelCart.addProduct(Cookies("Schoko-Doppelkekse", 1.0, 2));
	
    Cookies lebkuchen("Lebkuchen", 0.25, 4);
	lebkuchen.setExpired();
	kruemelCart.addProduct(lebkuchen);
	kruemelCart.addProduct(Biscuits("Haselnuss-Waffeln", 0.4, 3));
	kruemelCart.addProduct(Biscuits("Vanille-Waffeln", 1.0, 4));
    
	Biscuits schokowaffeln("Schoko-Waffeln", 1.0, 4);
	schokowaffeln.setExpired();
	kruemelCart.addProduct(schokowaffeln);
	kruemelCart.addProduct(Cookies("Butterkeks", 0.5, 4));
	
	std::cout << kruemelCart << '\n';
}