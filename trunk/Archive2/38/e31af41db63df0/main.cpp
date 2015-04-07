#include <iostream>
#include <vector>
#include <initializer_list>
#include <sstream>
#include <string>
#include <stdexcept>
#include <map>

namespace Vec
{
    class Vector
    {
        std::vector<float> rep{};
        int size{};
    public:
        Vector(int i = 0) : rep{}, size{i}
        {
            std::vector<float> temp(i);
            rep = temp;
        }

        Vector(std::vector<float>& v)
        {
            if (v.size() > size)
                throw std::length_error{"Vector parameter has incorrect length: " + std::to_string(v.size()) + "... Allowed length is 0 to " + std::to_string(size) + " inclusive."};

            int count{0};
            for (auto i : v)
            {
                if (count < size)
                    rep.push_back(i);
            
                ++count;
            }
        }

        Vector(std::initializer_list<float> il)
        {
            int count{0};
            std::vector<float> temp{};
            for (auto f : il)
            {
                temp.push_back(f);
                ++count;
            }
            size = count;
            rep = temp;
        }

        ~Vector() = default;
        Vector& operator=(const Vector&) = default;
        Vector& operator=(Vector&&) = default;
        Vector(const Vector&) = default;
        Vector(Vector&&) = default;

        Vector operator=(const std::vector<float>& v)
        {
            int count{0};

            for (auto& i : v)
                if (count < size) rep.at(count++) = i;

            return *this;
        }

        float operator[](int index)
        {
            if (index >= size || index < 0)
                throw std::range_error{"Invalid index: " + std::to_string(index) + "... Supplied index must be between 0 and " + std::to_string(size) + " inclusive."};

            return rep.at(index);
        }

        std::vector<float> representation() const { return rep; }

        Vector operator+=(const Vector& v)
        {
            std::vector<float> temp{rep};
            int count{0};            

            for (auto& i : v.rep)
                temp.at(count++) += i;

            rep = temp;
            return *this;
        }

        Vector operator+=(const float& f)
        {
            std::vector<float> temp{rep};

            for (auto& i : temp)
                i += f;

            rep = temp;
            return *this;
        }

        Vector operator+=(const std::vector<float>& v)
        {
            if (v.size() != rep.size())
                throw std::length_error{"Cannot add vectors of different sizes"}; //should handle > size as well

            std::vector<float> temp{rep};
            int count{0};

            for (auto& i : v)
            {
                temp.at(count) += i;
                ++count;
            }

            rep = temp;
            return *this;
        }

        Vector operator-=(const Vector& v)
        {
            std::vector<float> temp{rep};
            int count{0};

            for (auto& i : v.rep)
                temp.at(count++) -= i;

            rep = temp;
            return *this;
        }

        Vector operator-=(const float& f)
        {
            std::vector<float> temp{rep};

            for (auto& i : temp)
                i -= f;

            rep = temp;
            return *this;
        }

        Vector operator-=(const std::vector<float>& v)
        {
            if (v.size() != rep.size())
                throw std::length_error{"Cannot subtract vectors of different sizes"};

            std::vector<float> temp{rep};
            int count{0};

            for (auto& i : v)
            {
                temp.at(count) -= i;
                ++count;
            }

            rep = temp;
            return *this;
        }

        Vector operator*=(const float& f)
        {
            std::vector<float> temp{rep};
    
            for (auto& i : temp)
                i *= f;

            rep = temp;
            return *this;
        }

        Vector operator*=(const std::vector<float>& v)
        {
            if (v.size() != rep.size())
                throw std::length_error{"Cannot multiply vectors of different sizes"}; 

            std::vector<float> temp{rep};
            int count{0};

            for (auto& i : v)
            {
                temp.at(count) *= i;
                ++count;
            }

            rep = temp;
            return *this;
        }

        Vector operator/=(const float& f)
        {
            std::vector<float> temp{rep};

            for (auto& i : temp)
                if (f > 0)
                    i /= f;

            rep = temp;
            return *this;
        }

        Vector operator/=(const std::vector<float>& v)
        {
            if (v.size() != rep.size())
                throw std::length_error{"Cannot divide vectors of different sizes"};

            std::vector<float> temp{rep};
            int count{0};

            for (auto& i : v)
                if (i > 0)
                {
                    temp.at(count) /= i;
                    ++count;
                }

            rep = temp;
            return *this;
        }

    };

    Vector operator+(const std::vector<float>& v1, const std::vector<float>& v2)
    {
        if (v1.size() != v2.size())
            throw std::length_error{"Cannot add vectors of differing lengths."};

        int count{0};
        std::vector<float> temp(v1.size());
        
        for (auto& i : v1)
        {
            temp.at(count) = i + v2.at(count);
            ++count;
        }
        
        Vector result{temp};
        return result;
    }

    Vector operator+(const std::vector<float>& v, const float& f)
    {
        std::vector<float> temp{v};
    
        for (auto& i : temp)
            i += f;

        Vector result{temp};
        return result;
    }

    Vector operator+(const Vector& vec, const float& f)
    {
        std::vector<float> temp{vec.representation()};

        for (auto& i : temp)
            i += f;

        Vector result{temp};
        return result;
    }

    Vector operator-(const std::vector<float>& v1, const std::vector<float>& v2)
    {
        if (v1.size() != v2.size())
            throw std::length_error{"Cannot subtract vectors of differing lengths."};

        int count{0};
        std::vector<float> temp(v1.size());
        
        for (auto& i : v1)
        {
            temp.at(count) = i - v2.at(count);
            ++count;
        }
    
        Vector result{temp};
        return result;
    }

    Vector operator-(const std::vector<float>& v, const float& f)
    {
        std::vector<float> temp{v};
        
        for (auto& i : temp)
            i -= f;

        Vector result{temp};
        return result;
    }

    Vector operator-(const Vector& vec, const float& f)
    {
        std::vector<float> temp{vec.representation()};
        
        for (auto& i : temp)
            i -= f;

        Vector result{temp};
        return result;
    }

    Vector operator*(const std::vector<float>& v1, const std::vector<float>& v2)
    {
        if (v1.size() != v2.size())
            throw std::length_error{"Cannot multiply vectors of differing lengths."};

        int count{0};
        std::vector<float> temp(v1.size());
        
        for (auto& i : v1)
        {
            temp.at(count) = i * v2.at(count);
            ++count;
        }
    
        Vector result{temp};
        return result;
    }

    Vector operator*(const std::vector<float>& v, const float& f)
    {
        std::vector<float> temp{v};
    
        for (auto& i : temp)
            i *= f;

        Vector result{temp};
        return result;
    }

    Vector operator*(const Vector& vec, const float& f)
    {
        std::vector<float> temp{vec.representation()};

        for (auto& i : temp)
            i *= f;

        Vector result{temp};
        return result;
    }

    Vector operator/(const std::vector<float>& v1, const std::vector<float>& v2)
    {
        if (v1.size() != v2.size())
            throw std::length_error{"Cannot divide vectors of differing lengths."};

        int count{0};
        std::vector<float> temp(v1.size());
        
        for (auto& i : v1)
        {
            if (v2.at(count) > 0)
                temp.at(count) = i / v2.at(count);
            else
                std::cout << "Attempt to divide by 0; target unchanged" << std::endl;

            ++count;
        }
        
        Vector result{temp};
        return result;
    }

    Vector operator/(const std::vector<float>& v, const float& f)
    {
        std::vector<float> temp{v};
    
        for (auto& i : temp)
        {
            if (f > 0)
                i /= f;
            else
                std::cout << "Attempt to divide by 0; target unchanged" << std::endl;
        }

        Vector result{temp};
        return result;
    }

    Vector operator/(const Vector& vec, const float& f)
    {
        std::vector<float> temp{vec.representation()};

        for (auto& i : temp)
        {
            if (f > 0)
                i /= f;
            else
                std::cout << "Attempt to divide by 0; target unchanged" << std::endl;
        }

        Vector result{temp};
        return result;
    }
}

class Mat4
{
    using Vector = Vec::Vector;
    std::vector<Vector> rep{};
    int vecSize{};
    int vecCount{};
public:
    Mat4(int m = 0, int n = 0) : rep{}, vecSize{n}, vecCount{m}
    {
        std::vector<Vector> temp{};
        for (auto i = 0; i < vecCount; ++i)
        {
            Vector v(vecSize);
            temp.push_back(v);
        }

        rep = temp;
    }

    Mat4(const std::vector<Vector>& v) : rep{v} 
    {
        if (v.size() > 0) vecSize = v.at(0).representation().size();
        else throw std::logic_error{"std::vector has length of 0"};
    
        vecCount = v.size();
    }

    Mat4(std::initializer_list<Vector> ilv)
    {
        int count{0};
        std::vector<Vector> temp{};
        for (auto i : ilv)
        {
            if (i.representation().size() > vecSize)
                vecSize = i.representation().size();

            if (count < vecSize)
            {
                temp.push_back(i);
                count++;
            }
            else
                break;
        }
        vecCount = count;
        rep = temp;
    }
    
    //default move and copy, and destructor are generated by the compiler
    
    Vector operator[](int index)
    {
        if (index < 0 || index >= vecSize)
            throw std::range_error{"Invalid index sent to Mat4::operator[](int);  0 <= index <= 3"};

        return rep.at(index);
    }

    std::vector<Vector> representation() const { return rep; }

    int getVecCount() const { return vecCount; }
    int getVecSize() const { return vecSize; }

};

Mat4 operator+(const Mat4& l, const Mat4& r)
{
    std::vector<Vec::Vector> temp{};
    int count{0};

    for (auto& i : l.representation())
        temp.push_back(i);
    
    for (auto& i : r.representation())
        temp.at(count++) += i;
    
    Mat4 result{temp};
    return result;
}

Mat4 operator-(const Mat4& l, const Mat4& r)
{
    std::vector<Vec::Vector> temp{};
    int count{0};

    for (auto& i : l.representation())
        temp.push_back(i);
    
    for (auto& i : r.representation())
        temp.at(count++) -= i;
    
    Mat4 result{temp};
    return result;
}

Mat4 operator*(const Mat4& m, const int& scalar)
{
    std::vector<Vec::Vector> temp{};

    for (auto&i : m.representation())
        temp.push_back(i * scalar);

    Mat4 result{temp};
    return result;
}

Mat4 rotateAntiClockwise(const Mat4& m)
{
    using namespace std;
    std::map<int, Vec::Vector> rows{};
    std::map<int, std::vector<float>> elems{};
    
    //this eliminates magic numbers and many variables
    std::vector<Vec::Vector> rv(m.getVecSize());
    for (int i = 0; i < m.getVecSize(); ++i)
        rows[i] = rv.at(i);

    //as above
    std::vector<std::vector<float>> rf(m.getVecSize());
    for (int i = 0; i < m.getVecSize(); ++i)
        elems[i] = rf.at(i);

    for (auto& i : m.representation()) //for every Vector
    {   
        for (int j = 0; j < m.getVecSize(); ++j) //for every element in every vector in the Vector
        {
            elems[j].push_back(i.representation().at(j));
            rows[j] = elems[j];
            for (auto k : rows[j])
            {
                cout <<" Hey" << endl;
            }
        }
    }

    std::vector<Vec::Vector> temp{};
    for (int i = m.getVecSize() - 1; i >= 0; --i){
        temp.push_back(rows[i]);
        cout << temp.size() << endl;
    }
    
    Mat4 result{temp};
    return result;
}

Mat4 reverse(const Mat4& m)
{
    std::vector<Vec::Vector> temp(4);
    int count{0};

    for (auto& i : m.representation())
        temp.at(count++) = i;

    std::swap(temp.at(0), temp.at(3));
    std::swap(temp.at(1), temp.at(2));
    Mat4 result{temp};
    return result;
}

Mat4 operator*(const Mat4& l, const Mat4& r)
{
    Mat4 transformed{reverse(rotateAntiClockwise(r))};
    std::vector<Vec::Vector> rows{(l.getVecSize() == r.getVecSize() ? l.getVecSize() : -1)};
    int rowCount{0};

    for (auto& i : l.representation()) //for every row
    {
        std::vector<float> elems(l.getVecSize());
        for (int j = 0; j < l.getVecSize(); ++j)
        {
            int elemCount{0};
            for (auto& k : transformed.representation())
                elems.at(elemCount++) += k.representation().at(j) * i.representation().at(j);
        } 
        rows.at(rowCount++) = elems;
    }

    Mat4 result{rows};
    return result;
}

std::ostream& operator<<(std::ostream& os, const Mat4& m)
{
    for (auto i : m.representation())
    {
        for (auto j : i.representation())
            os <<  j << ' ';
        os << std::endl;
    }
    return os;
}

int main()
{

    using namespace std;
    using namespace Vec;
    
    Vector test0{2.0, 4.5, 66.6, 99.99};
    Vector test1{2.1, 5.5, 33.3, 0.01};
    try
    {
        Mat4 m0{test0, test0, test0, test0};

        Vector v1{2, 3, 9, 7};
        Vector v2{9, 7, 5, 4};
        Vector v3{2, 1, 4, 6};
        Vector v4{8, 9, 3, 8};
        Mat4 m1{v1, v2, v3, v4};

        //try{m0 = m1 * m1;}catch(...){cout << "oops" << endl;}

        m0 = rotateAntiClockwise(m0);
        cout << m0 << endl;

    }
    catch (range_error e)
    {
        cerr << e.what() << endl;
    }
    catch (length_error e)
    {
        cerr << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Something disastrous happened!" << endl;
    }
}



