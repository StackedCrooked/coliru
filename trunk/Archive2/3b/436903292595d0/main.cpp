#include <iostream>
#include <array>
#include <string>
#include <vector>


using Position3 = std::array<float, 3>;
using Plane = std::array<Position3, 4>;

Position3& operator *= (Position3& pos, const float scale)
{
    for (auto& x : pos) x *= scale;
    return pos;
}

Position3 operator * (const Position3& pos, const float scale)
{
    Position3 result = pos;
    result *= scale;
    return result;
}

Position3& operator += (Position3& left, const Position3& right)
{
    for (size_t i = 0; i < 3; i++)
        left[i] += right[i];

    return left;
}

Position3 operator + (const Position3& left, const Position3& right)
{
    Position3 result = left;
    result += right;
    return result;
}

Position3& operator -= (Position3& left, const Position3& right)
{
    for (size_t i = 0; i < 3; i++)
        left[i] -= right[i];

    return left;
}

Position3 operator - (const Position3& left, const Position3& right)
{
    Position3 result = left;
    result -= right;
    return result;
}


/* vertices by index in quad:
    3---------2
    |         |
    |         |
    |         |
    0---------1
*/
std::vector<Plane> subdivide(const Plane& plane, size_t iterations = 1)
{
    if (iterations == 0)
    {
        return{ plane };
    }
    else
    {
        Position3 e1 = plane[1] - plane[0];
        Position3 e2 = plane[2] - plane[3];
        Position3 e3 = plane[3] - plane[0];
        Position3 e4 = plane[2] - plane[1];

        Position3 p1 = e1 * 0.5f + plane[0];
        Position3 p2 = e2 * 0.5f + plane[3];
        Position3 p3 = e3 * 0.5f + plane[0];
        Position3 p4 = e4 * 0.5f + plane[1];

        Position3 e5 = p2 - p1;
        Position3 p5 = e5 * 0.5f + p1;

        std::vector<Plane> result{
            { plane[0], p1, p5, p3 },
            { p1, plane[1], p4, p5 },
            { p5, p4, plane[2], p2 },
            { p3, p5, p2, plane[3] }
        };

        if (iterations == 1)
        {
            return result;
        }
        else
        {
            std::vector<Plane> result2;
            for (auto& x : result)
            {
                auto subplanes = subdivide(x, iterations - 1);
                result2.insert(result2.end(), subplanes.begin(), subplanes.end());
            }
            return result2;
        }
    }
}

int main()
{
    Plane p = { { { 0, 0 }, { 1, 0.5f }, { 1, 1 }, { -0.5f, 1.5f } } };

    auto subd = subdivide(p, 2);

    std::string vertices;
    std::string faces;

    size_t idx = 1;
    for (auto& plane : subd)
    {
        for (auto& pos : plane)
            vertices.append("v  ").append(std::to_string(pos[0])).append(" ").append(std::to_string(pos[1])).append(" ").append(std::to_string(pos[2])).append("\n");

        faces.append("f ").append(std::to_string(idx)).append(" ").append(std::to_string(idx + 1)).append(" ").append(std::to_string(idx + 2)).append(" ").append(std::to_string(idx + 3)).append("\n");

        idx += 4;
    }
    std::string obj = vertices + "\n\n" + faces;

    std::cout << obj;
}