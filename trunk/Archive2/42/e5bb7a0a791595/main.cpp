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
	friend struct stream_writer;
public:
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

struct stream_writer
{
	template <typename W, typename T>
	W& operator()(W& w, const T& t) {
		w.s << t;
		return w;
	}
};

template <typename T, typename STREAM>
writer<STREAM>& operator<<(writer<STREAM>& w, const T& t) {
    return stream_writer()(w, t);
}

int main() {
	writer<htmlstream> hw;
	hw << 4;
	cout << hw.write() << endl;
}