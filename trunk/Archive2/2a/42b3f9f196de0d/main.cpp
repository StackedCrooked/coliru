#include <iostream>
#include <vector>

// point in 3d space
struct IgPoint {
    float m_X;
    float m_Y;
    float m_Z;
};

// plane in 3d space
struct IgPlane {
    float m_A;
    float m_B;
    float m_C;
    float m_D;
};

void partitionPoints(IgPoint* points, int numPoints, const IgPlane* plane)
{
    std::vector<IgPoint> pointsBehind; int pbIndex = 0;
    std::vector<IgPoint> pointsFront; int pfIndex = 0;
    IgPoint planePoint;
    planePoint.m_X = plane->m_D / plane->m_A;
    planePoint.m_Y = 0.0;
    planePoint.m_Z = 0.0;

    for(int index = 0; index < numPoints; ++index) {
        float num;
        // vec3(PQ) dot plane normal
        num = (points[index].m_X - planePoint.m_X) * plane->m_A
               + points[index].m_Y * plane->m_A
               + points[index].m_Z * plane->m_A;

        // if the distance from the plane to the point is negative then it is
        // behind the plane, else if it is positive then it is in front of the
        // plane
        if (num < 0) {
            pointsBehind.push_back(points[index]);
            pbIndex++;
        } else if (num > 0) {
            pointsFront.push_back(points[index]);
            pfIndex++;
        }
    }

    int resultIndex = 0;
    // put behind points in final array
    for (int behindIndex = 0; behindIndex < pbIndex; behindIndex++) {
        points[resultIndex] = pointsBehind[behindIndex];
        resultIndex++;
    }

    // put front points in final array
    for (int frontIndex = 0; frontIndex < pfIndex; frontIndex++) {
        points[resultIndex] = pointsFront[frontIndex];
        resultIndex++;
    }

    // zero out the remaining points since they are on the plane... just
    // in case they exist
    while(resultIndex < numPoints){
        points[resultIndex].m_X = 0.0;
        points[resultIndex].m_Y = 0.0;
        points[resultIndex].m_Z = 0.0;
        resultIndex++;
    }
}

int main()
{
    IgPoint points[10] = {
        { 1.0, 1.0, 1.0},
        {-1.0, -1.0, -1.0},
        { 2.0, 2.0, 2.0},
        {-2.0, -2.0, -2.0},
        { 3.0, 3.0, 3.0},
        {-3.0, -3.0, -3.0},
        { 4.0, 4.0, 4.0},
        {-4.0, -4.0, -4.0},
        { 5.0, 0.0, 0.0},
        {-5.0, 0.0, 0.0},
    };
    IgPlane plane = {3.0, 2.0, 4.0, 12.0};
    partitionPoints(points, 10, &plane);

    for (int i = 0; i < 10; i++) {
        std::cout << "{" << points[i].m_X << ", "
                  << points[i].m_Y << ", "
                  << points[i].m_Z << "}" << std::endl;
    }
}