#include <iostream>

struct SomeStruct {

    SomeStruct() {

	}
	SomeStruct(float x) {
		init(x);
	}

	float x;
	bool isValid = true;

	void init(float x)
	{
		this->x = x;
	}
	void init(float x, bool isValid)
	{
		this->x = x;
		this->isValid = isValid;
	}

	void copy(const SomeStruct& s)
	{
		this->init(s.x, s.isValid);
	}

	// assingment operators
	SomeStruct& operator= (const SomeStruct& s) {
		// Check for self-assignment!
		if (this == &s)
			return *this;

		this->copy(s);
		return *this;
	}
};


int main()
{
    
    int invalidCount = 0;

    for (int i = 0; i < 1000; i++) {
		SomeStruct afaweafwePt = SomeStruct(i);
		if (!afaweafwePt.isValid) {
			invalidCount++;
		}
		std::cout << "afaweafwePt: " << (afaweafwePt.isValid ? "true" : "false") << " " << afaweafwePt.isValid << ": " << afaweafwePt.x << std::endl;
	}

	std::cout << "invalid: " << invalidCount << std::endl;
}