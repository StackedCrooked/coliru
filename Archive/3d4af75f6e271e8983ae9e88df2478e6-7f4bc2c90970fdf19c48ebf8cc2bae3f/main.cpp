#include <iostream>

int main() {
    using namespace std;
    int size;
    cout << "enter array size:";
    cin >> size;
    int i, score[size], max; //array size set to variable doesn't fail
    cout << endl << "enter scores:\n";
    cin >> score[0];
    max = score[0];
    for (i = 1; i < size; i++)
    {
        cin >> score[i];
        if (score[i] > max)
    max = score[i];
    }
    cout << "the highest score is " << max << endl;
    return 0;
}