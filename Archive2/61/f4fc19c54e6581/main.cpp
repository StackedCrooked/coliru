class Base {
private:
    int* array;
public:
    Base(int* a) {
        array = a;
        for(int i = 0 ; i < 10 ; i++) {
            array[i] = i;
        }
    }
};

class Child : public Base {
private:
    int* array;
public:
    Child() : array(new int[10]), Base(array) {}
    void print() {
        for(int i = 0 ; i < 10 ; i++) {
            cout << array[i] << endl;
        }
    }
};

int main() {
    
}