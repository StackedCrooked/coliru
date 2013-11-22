int main() {
    const char* str = "hi";
    delete str;
    char* str2 = new char[10];
    delete str2;
}