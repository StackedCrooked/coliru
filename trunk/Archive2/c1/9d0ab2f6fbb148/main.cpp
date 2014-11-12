#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric::ublas;

const static int record_num = 270;
const static int dim_num = 13;

bool debug = false;

// the vector for the category 1 * 270
boost::numeric::ublas::vector<double> y(record_num);

// the matrix for the features 270 * 13
boost::numeric::ublas::matrix<double> x(record_num, dim_num);

typedef boost::numeric::ublas::vector<double> d_vector;


double norm(const d_vector& v1, const d_vector& v2) {
    assert (v1.size() == v2.size());
    double sum = 0;
    for (size_t i=0; i<v1.size(); ++i)
    {
        double minus = v1(i) - v2(i);
        double r = minus * minus;
        sum += r;
    }

    return sqrt(sum);
}

template < class T> 
void convert_from_string(T& value, const string& s)
{
    stringstream ss(s);
    ss >> value;
}

int get_cat(const string& data) {
    int c;
    convert_from_string(c, data);
    
    return c;
}

bool get_features(const string& data, int& index, double& value) {
    int pos = data.find(":");
    if (pos == -1) return false;
    convert_from_string(index, data.substr(0, pos));
    convert_from_string(value, data.substr(pos + 1));

    return true;
}


bool parse_line(const string& line, int& cat, const int line_num) {
    if (line.empty()) return false;
    size_t start_pos = 0;
    char space = ' ';

    while (true) {
        size_t pos = line.find(space, start_pos);

        if ((int)pos != -1) {
            string data = line.substr(start_pos, pos - start_pos);
            if (!data.empty()) {
                if (start_pos == 0) {
                    cat = get_cat(data);
                }
                else {
                    int index = -1;
                    double v = 0;
                    get_features(data, index, v);
                    if (debug)
                        cout << "index: " << index << "," << "value: " << v << endl;
                    if (index != -1) {
                        index -= 1; // index from 0
                        x(line_num, index) = v;
                    }
                }
            }
            start_pos = pos + 1;
        }
        else {
            string data = line.substr(start_pos, pos - start_pos);
            if (!data.empty()) {
                cout << "read data: " << data << endl;
                int index = -1;
                double v = 0;
                get_features(data, index, v);
                if (debug)
                    cout << "index: " << index << "," << "value: " << v << endl;
                if (index != -1) {
                    index -= 1; // index from 0
                    x(line_num, index) = v;
                }
            }
            break;
        }
    }

    return true;

}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " data_file" << endl;
        return -1;
    }

    string path(argv[1]);

    ifstream in(path.c_str());
    string line;
    int line_num = 0;
    if (in.is_open()) {
        while (in.good()) {
            getline(in, line);
            if (line.empty()) continue;
            int cat = 0;
            if (!parse_line(line, cat, line_num)) {
                cout << "parse line: " << line << ", failed.." << endl;
                continue;
            }

            y(line_num) = cat;

            line_num += 1;
        }
        in.close();
    }
    
    double epsilon = 0.0003;
    double gamma = 0.0001;

    boost::numeric::ublas::vector<double> weight_old(dim_num);
    for (size_t i=0; i<weight_old.size(); ++i) {
        weight_old(i) = 1;
    }
    int iter = 0;

    boost::numeric::ublas::matrix<double> prod_2_matrix(prod(trans(x), x));
    boost::numeric::ublas::vector<double> vector_x_prod_y(prod(trans(x), y));


    while (true) {
        double factor = norm(prod(x, weight_old), y);
        double target = 0.5 * factor * factor;
        cout << "the " << iter << " th iteration: target=" << target << endl; 
        boost::numeric::ublas::vector<double> weight_new(weight_old - gamma * (prod(prod_2_matrix, weight_old) - vector_x_prod_y));
        if (norm(weight_new, weight_old) < epsilon) {
            cout << "the best weight: " << weight_new << endl;
            break;
        }
        else {
            weight_old = weight_new;
        }

        iter += 1;
    }

    return 0;
}