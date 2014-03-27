#include <iostream>
#include <sstream>

using namespace std;

template<typename tag>
struct stream {
    std::stringstream ss;
	std::string str() const { return ss.str(); };
};

struct html { };
struct json { };

template<typename T>
stream<html>& operator<<(stream<html>& hs, const T& t) {
	hs.ss << "<div>" << t << "</div>";
	return hs;
}

template<typename T>
stream<json>& operator<<(stream<json>& js, const T& t) {
	js.ss << "{ \"t\": " << t << " }";
	return js;
}

int main() {
	stream<html> hs;
	stream<json> js;
	hs << 4;
	js << 4;
	cout << hs.str() << endl;
	cout << js.str() << endl;
}
