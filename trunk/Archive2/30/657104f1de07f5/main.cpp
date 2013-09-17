int main() {
    int& i = *(new int);
    delete &i;
}