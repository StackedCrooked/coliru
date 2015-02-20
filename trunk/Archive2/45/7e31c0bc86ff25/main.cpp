#include <vector>

using namespace std;

#define CIRCULAR_BUFFER_DEFAULT_SIZE 5000

template <typename T>
class CircularVector {
public:
    CircularVector(int size) {
		_size = size;
		_v.reserve(_size);
	}

	CircularVector() {
		_size = CIRCULAR_BUFFER_DEFAULT_SIZE;
		_v.reserve(_size);
	}
    
    template <typename ...Args>
	void emplace(Args&... args) {
		++Count;
		++_indexWrite;
		if (_indexWrite > _size - 1) _indexWrite = 0;
		_v[_indexWrite] = T(args...);
	}

	void push(const T& item) {
		++Count;
		++_indexWrite;
		if (_indexWrite > _size - 1) _indexWrite = 0;
		_v[_indexWrite] = item;
	}

	void pop(T& item) {
		item = _v[_indexRead];
		++_indexRead;
		if (_indexRead > _size - 1) _indexRead = 0;
		--Count;
	}

	T& back() {
		return _v[(_indexRead + Count - 1) % _size];
	}


	void erase(int numItems) {
		_indexRead += numItems;
		if (_indexRead > _size - 1) _indexRead -= _size;
		Count -= numItems;
	}

	void eraseAt(int index) {
		swap(_v[index], _v[(_indexRead + Count - 1) % _size]);
		--Count;
		--_indexWrite;
		if (_indexWrite < 0) {
			_indexWrite = _size - 1;
		}
	}

	void clear() {
		_indexRead = 0;
		_indexWrite = -1;
		Count = 0;
	}


	T& operator[](std::size_t idx) {
		int index = _indexRead + idx;
		if (index > _size) index = index % _size;
		return _v[index];
	};

	int Count = 0;

private:
	int _indexWrite = -1;
	int _indexRead = 0;
	int _size = 0;

	std::vector<T> _v;
};


class Item {
public:
	double A;
	int B;
	int C;
	vector<int> D;
	int E;

	Item(double a, int b, int c, vector<int> &d, int e) {
        A = a;
        B = b;
        C = c;
        D = d;
        E = e;
	}
};

int main() {
    CircularVector<Item> v;
    v.emplace(1, 0, 1, 0, 1, 0, vector<int>(), -1);
}