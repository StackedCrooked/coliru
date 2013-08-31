class String{
    char* arr;
    int len;

    String& operator[](int);
};

String& String::operator[](int n) {
len = 1;
arr = new char[1];
arr = *arr[n];
}

int main() {}