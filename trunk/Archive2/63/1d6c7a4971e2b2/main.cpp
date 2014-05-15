#include <iostream>

struct vertex
{
    char x;
    char y;
    char z;
};


struct vertexinfo_1 
{
    char vertex_count;
    const vertex* vertices;
};

struct vertexinfo_2
{
    char vertex_count;
    const vertex vertices[];
};

// Consists of amount then vertices.
const char DATA[] = { 0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09 };

int main()
{
    vertexinfo_1 vinf1;
    vinf1.vertex_count = DATA[0];
    vinf1.vertices = (const vertex*)(DATA + 1);
    const vertexinfo_2* vinf2 = (const vertexinfo_2*)(DATA);
    for (int i = 0; i != vinf1.vertex_count; i++) {
    std::cout << "vertice " << i << " in vinf1: {" << int(vinf1.vertices[0].x) << ", "  << int(vinf1.vertices[0].y) << ", "  << int(vinf1.vertices[0].z) << "}" <<  std::endl;
    std::cout << "vertice " << i << " in vinf2: {" << int(vinf2->vertices[0].x) << ", "  << int(vinf2->vertices[0].y) << ", "  << int(vinf2->vertices[0].z) << "}" << std::endl;
    }
    return 0;
}