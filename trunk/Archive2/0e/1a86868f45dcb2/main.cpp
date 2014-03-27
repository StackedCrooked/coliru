#include <iostream>
#include <sstream>
using namespace std;

struct stream {
    std::stringstream ss;
    string str() const { return ss.str(); }
};
class htmlstream : public stream {
};
class jsonstream : public stream {
};

template <typename STREAM>
class writer {
    STREAM s;
public:
    template <typename T> writer& operator<<(const T& t) {
		s << t;
		return *this;
	}
	int write() {
		cout << "writing: " << s.str() << endl;
		return 0;
	}
};

template <typename T> htmlstream& operator<<(htmlstream& hs, const T& t) {
    hs.ss << "<div>" << t << "</div>";
    return hs;
}
template <typename T> jsonstream& operator<<(jsonstream& js, const T& t) {
    js.ss << "{ \"t\": " << t << " }";
    return js;
}

int main() {
	writer<htmlstream> hw;
	hw << 4;
	cout << hw.write() << endl;
}