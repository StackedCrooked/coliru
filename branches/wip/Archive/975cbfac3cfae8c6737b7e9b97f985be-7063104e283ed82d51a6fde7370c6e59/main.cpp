#include <iostream>

using namespace std;

class ScreenCls {
public:
    typedef string::size_type pos;
	ScreenCls() { }
	ScreenCls(pos height, pos width, char c): height(height), width(width), contents(height * width, c) { }

	ScreenCls &set(char);
	ScreenCls &set(pos, pos, char);

	char get() const { return contents[cursor]; }  // Implicitly inline
	inline char get(pos height, pos width) const;  // Made inline explicit

	ScreenCls &move(pos r, pos c);
	void someMemberFunction() const;

private:
	mutable pos accessCounter;  // Mutable members may be changed even in const member functions
	pos cursor;
	pos height;
	pos width;
	string contents;
};

char ScreenCls::get(pos r, pos c) const {
    pos row = r * width;
	return contents[row + c];
}

inline ScreenCls &ScreenCls::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;
	return *this;
}

void ScreenCls::someMemberFunction() const {
	++accessCounter;
}

ScreenCls &ScreenCls::set(char ch) {
	contents[cursor] = ch;
	return *this;
}

ScreenCls &ScreenCls::set(pos r, pos c, char ch) {
	contents[r * width + c] = ch;
	return *this;
}

int main() {
}