#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <type_traits>

#define SAY(s) std::cout << s << std::endl;

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    int width;
    int height;
public:
    Matrix(int width, int height) : width(width), height(height) {
//        SAY("SUP")
        for(int i = 0; i < width; i++) {
//            SAY("addrow")
            data.push_back(std::vector<T>());
            for(int j = 0; j < height; j++) {
//                SAY("\taddcol")
//                std::cout << "(" << i << ", " << j << ")" << std::endl;
                data[i].push_back(0);
            }
        }
    }
    
    Matrix(std::vector<std::vector<T>> matrixData) {
//        SAY("HERROW")
        width = matrixData.size();
        height = matrixData[0].size();
        data = matrixData;
    }
    
    void print() {
        for(int y = 0; y < height; y++) {
            for(int x = 0; x < width; x++) {
                    std::cout << data[x][y];
                if(x != (width-1))
                    std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
    
    void set(int x, int y, T value) {
        data[x][y] = value;   
    }
    
    T get(int x, int y) {
        return data[x][y];
    }
    
    int getWidth() { return width; }
    
    int getHeight() { return height; }
};

template<typename T1, typename T2>
Matrix<double> multiplyMatrix(Matrix<T1> a, Matrix<T2> b)
{
    if(std::is_floating_point<T1>() | std::is_floating_point<T2>())
        std::cout << "isfloating" << std::endl;
    int width = a.getWidth() > b.getWidth() ? a.getWidth() : b.getWidth();
    int height = a.getHeight() > b.getHeight() ? a.getHeight() : b.getHeight();
    Matrix<double> resultant(width, height);
    std::cout << "It's alive(" << width << ", " << height << ")" << std::endl;
    for (int cols = 0; cols < resultant.getWidth(); cols++) {
//        std::cout << "cols:" << cols << std::endl;
    	for (int rows = 0; rows < resultant.getHeight(); rows++) {
//            std::cout << "rows:" << rows << std::endl;
            double tmp = 0.0;
            if(a.getWidth() == resultant.getWidth()) {
    			for (int inner = 0; inner < a.getHeight(); inner++) {
//                    std::cout << "inner:" << inner << std::endl;
        		    tmp += a.get(cols, inner) * b.get(inner, rows);
    			}
            }
            else {
        		for (int inner = 0; inner < a.getWidth(); inner++) {
//                    std::cout << "inner:" << inner << std::endl;
        		    tmp += a.get(inner, rows) * b.get(cols, inner);
    			}
			}
            resultant.set(cols, rows, tmp);
		}
	}
    return resultant;
}

//template <typename T1, typename T2>
//using multiply<T1,T2>() = multiplyMatrix<T1,T2,double>();

int main()
{
//    Matrix<int> a({{1, 2, 3},{4, 5, 6}, {7, 8, 9}});
//    
//    Matrix<int> b({{10, 11, 12},{13, 14, 15}, {16, 17, 18}});
//    
//    a.print();
//    std::cout << "--------" << std::endl;
//    b.print();
//    std::cout << "--------" << std::endl;
//    
//    Matrix<int> o = multiplyMatrix(b, a);
//    o.print();
//    std::cout << "--------" << std::endl;
//    
//    Matrix<int> p({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
//    p.print();
//    std::cout << "--------" << std::endl;
    
    double rad = ((45*180)/M_PI);
	Matrix<double> transformation({{cos(rad), sin(rad), 0.0},{-sin(rad), cos(rad), 0.0},{0.0, 0.0, 1.0}});
    transformation.print();
    std::cout << "--------" << std::endl;
    Matrix<double> position({{1.0, 0.0, 0.0},{0.0, 1.0, 0.0},{5.0, 5.0, 1.0}});
    position.print();
    std::cout << "--------" << std::endl;
    
    Matrix<double> result = multiplyMatrix(transformation, position);
    result.print();
////    transformation.print();
}
