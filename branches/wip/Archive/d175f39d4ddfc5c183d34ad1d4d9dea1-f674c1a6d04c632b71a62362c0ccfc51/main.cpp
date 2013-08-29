
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

class Blur {
public:
    Blur() {};
    virtual void blur(int **pixels, int height, int width, int i, int j) = 0;
    virtual ~Blur() {};
};

class Blur4X : public Blur {
public:
    Blur4X() {};
    virtual ~Blur4X() {};
    virtual void blur(int **pixels, int height, int width, int i, int j) {
        int iMaxI;
        int iMaxJ;
        int **p = pixels;
        iMaxI = std::min(height - 1, i + 1);
        iMaxJ = std::min(width - 1, j + 1);
        p[i][j] = (int)(((long long)p[i][j] + p[iMaxI][iMaxJ] + p[iMaxI][j] + p[i][iMaxJ])/4);
    }
};

class Blur9X : public Blur {
public:
    Blur9X() {};
    ~Blur9X() {};

    virtual void blur(int **pixels, int height, int width, int i, int j) {
        int iMaxI;
        int iMaxJ;
        int iMinI;
        int iMinJ;
        int **p = pixels;

        iMinI = std::max(0, i - 1);
        iMinJ = std::max(0, j - 1);
        iMaxI = std::min(height - 1, i + 1);
        iMaxJ = std::min(width - 1, j + 1);
        p[i][j] =
                (int)((((long long)p[iMinI][iMinJ] + p[iMinI][j] + p[iMinI][iMaxJ] +
                p[i][iMinJ] + p[i][j] + p[iMinI][i] +
                p[iMaxI][iMinJ] + p[iMaxI][j] + p[iMaxI][iMaxJ]) * 477218589) >> 32);

    }
};

static const int WIDTH = 5000;
static const int HEIGHT = 5000;

void fill_array(int **array, int height, int width);
void fill_array_zeros(int **array, int height, int width);

int main() {
    unsigned startTime = clock();

    srand(time(NULL));
    int **array;
    array = new int*[HEIGHT];
    fill_array(array, HEIGHT, WIDTH);

    Blur *blur;

    blur = new Blur4X();
    for(int i = 0; i < HEIGHT; i++){
        for (int j = 0; j  < WIDTH; j++){
            blur->blur(array, HEIGHT, WIDTH, i, j);
        }
    }
    delete blur;

    blur = new Blur9X();
    for(int i = 0; i < HEIGHT; i++){
        for (int j = 0; j  < WIDTH; j++){
            blur->blur(array, HEIGHT, WIDTH, i, j);
        }
    }
    delete blur;

    cout << clock() - startTime << endl;
    return 0;
}

void fill_array(int **array, int height, int width){
    for(int i = 0; i < height; i++){
        array[i] = new int[width];
        for(int j = 0; j < width; j++){
            array[i][j] = rand();
        }
    }
}

void fill_array_zeros(int **array, int height, int width){
    for(int i = 0; i < height; i++){
        array[i] = new int[width];
        memset(array[i], 0, sizeof(int) * width);
    }
}
