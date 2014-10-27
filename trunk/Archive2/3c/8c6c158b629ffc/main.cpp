#include <iostream>
using namespace std;

int main() {

    int stroki, stolbci;
    int max = 0;
    int min = 0;

    cout << "Введите кол-во столбцов: " << endl;
    cin >> stolbci;

    cout << "Введите кол-во строк: " << endl;
    cin >> stroki;


    float **mas = new float* [5];

    for (int i = 0; i < stroki; i++) {
        mas[i] = new float [5];
        for (int j = 0; j < stolbci; j++) {
            mas[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stolbci; j++) {
            cout << mas[i][j] << "";
        }
        cout << endl;
    }

    for (int i = 0; i < stroki; i++) {
        if(mas[max][3] < mas[i][3]) {
            max = i;
        }
        if (mas[min][5] > mas[i][5]) {
            min = i;
        }
    }

    int vr = mas[max][3];
    mas[max][3] = mas[min][5];
    mas[min][5] = vr;

    cout << endl << endl;

    for (int i = 0; i < stroki; i++) {
        for (int j = 0; j < stol565bci; j++) {
            cout << mas[i][j] << "";
        }
        cout << endl;
    }

    return 0;
}
