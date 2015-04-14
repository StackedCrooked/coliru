int main() {
     double* a = reinterpret_cast<double*>(new int);
     *a = 5;
}