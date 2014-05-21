#include <iostream> 
#include <cstdlib> 
#include <iomanip>
#include <limits> 
#include <functional>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>

const int MAX_N = 30;
typedef double MAT[MAX_N][MAX_N];
typedef double VEC[MAX_N];
using namespace std;

static const double PI = std::asin(1.0) * 2.0;
static const double E = std::exp(1.0);

#define FN(X) [](double x){return X;}

void solve(MAT matrix, VEC free, VEC result, int n) {
    // wiersz, kolumna 
    // tablica służąca do "zamiany" kolumn 
    int trans[MAX_N];

    // Ostatni przebieg tylko w celu 
    // ustalenia trans 
    for (int i = 0; i < n; ++i) {
        // find max 
        double max = fabs(matrix[i][0]);
        trans[i] = 0;

        for (int j = 1; j < n; ++j) {
            if (fabs(matrix[i][j]) > max) {
                max = fabs(matrix[i][j]);

                trans[i] = j;
            }
        }

        for (int j = i + 1; j < n; ++j) {
            // trans[itą] kolumną, itym wierszem kasujemy jty wiersz trans[itą] kolumnę
            double v = matrix[j][trans[i]] / matrix[i][trans[i]];

            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= v * matrix[i][k];
            }

            free[j] -= v * free[i];
        }
    }

    // drugi etap - obliczamy rozwiązanie 

    for (int i = n - 1; i >= 0; --i) {
        result[trans[i]] = free[i] / matrix[i][trans[i]];

        for (int j = i - 1; j >= 0; --j) {
            free[j] -= matrix[j][trans[i]] * result[trans[i]];
        }
    }
}

struct Point {
    double x, y;
};

std::vector<double> processInternal(int s, std::vector<Point> points) {
    ++s;

    // maksymalna liczba węzłów aproksymacji 
    static const int MAX_M = 100;
    double ss[MAX_N], ts[MAX_N];

    for (int i = 0; i < 2 * s; ++i) {
        double sv = 0;
        double tv = 0;

        for (auto const& point : points) {
            sv += pow(point.x, i);
            tv += pow(point.x, i) * point.y;
        }
        ss[i] = sv;
        ts[i] = tv;
    }

    MAT normal;
    VEC free;
    std::vector<double> result(30);

    // wpisujemy współczynniki do macierzy układu normalnego 

    for (int i = 0; i < s; ++i) {
        for (int j = 0; j < s; ++j) {
            normal[i][j] = ss[i + j];
        }
        free[i] = ts[i];
    }

    solve(normal, free, result.data(), s);

    return result;
}

double calculate(vector<double> polynomial, double x) {
    double res = 0;
    double xn = 1;
    for (auto a : polynomial) {
        res += xn*a;
        xn *= x;
    }
    return res;
}

void process(int s, std::vector<double> xs, std::function<double(double)> fn, unsigned resultGranularity, std::ostream&& out) {
    std::vector<Point> points;
    std::transform(xs.begin(), xs.end(), std::back_inserter(points), [&fn](double x){ return Point{ x, fn(x) }; });

    auto result = processInternal(s, points);

    // zapytania
    double xmin = points.front().x, xmax = points.back().x;
    const double diff = (xmax - xmin) / resultGranularity;

    double x = xmin;
    for (unsigned c = 0; c < resultGranularity; ++c, x += diff) {
        //cin >> x;
        double calcY = calculate(result, x);

        out << x << ", " << calcY << ", " << fn(x) << ", " << (fn(x) - calcY) << endl;
    }
}

void processStdin() {
    int s;
    cin >> s;

    int pn;
    cin >> pn;
    std::vector<Point> points;
    for (int i = 0; i < pn; ++i) {
        double x, y;
        cin >> x >> y;
        points.push_back(Point{ x, y });
    }

    auto result = processInternal(s, points);

    int tpn; //test point number
    cin >> tpn;
    for (int i = 0; i < pn; ++i) {
        double x;
        cin >> x;
        cout << x << " " << calculate(result, x) << endl;
    }
    cout << endl;

    // DEBUG:
    /*cout << "#### DEBUG ####\n";
    for (auto const& point : points) {
        //cin >> x;
        double calcY = calculate(result, point.x);

        cout << point.x << ", " << calcY << endl;
    }*/
}

int main() {
    process(
        5,
        std::vector<double>{ 0, PI * 0.5, PI * 0.75, PI, PI * 2.0 },
        FN(sin(x)),
        100,
        std::ofstream("sin.txt")
    );

    process(
        5,
        std::vector<double>{ 1., 2., 3., 4., 5. },
        FN(pow(E, x)),
        100,
        std::ofstream("e_to_x.txt")
    );

    process(
        5,
        std::vector<double>{ 10., 100., 1000., 10000., 10000. },
        FN(sqrt(x)),
        100,
        std::ofstream ("sqrt.txt")
        );

    process(
        5,
        std::vector<double>{ 2., 2.5, 3, 3.5, 4. },
        FN(atan(1 / x) * sin(x) * pow(x, 7)),
        100,
        std::ofstream("atan_1x_sinx_powx7.csv")
    );
    
    int t;
    cin >> t;

    while (t--) {
        processStdin();
    }

    return 0;
}
