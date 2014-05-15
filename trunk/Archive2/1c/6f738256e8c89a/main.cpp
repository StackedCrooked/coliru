#include <stdio.h>
#include <string.h>

typedef struct Vertex {
    float x;
    float y;
    float z;
    float u;
    float v;
} Vertex;

typedef struct VertexChunk1 {
    char a;
    char b;
    unsigned int count;
    Vertex vertices;
} VertexChunk1;

typedef struct VertexChunk2 {
    char a;
    char b;
    unsigned int count;
    Vertex vertices[];
} VertexChunk2;

main()
{
    int i;
    char buffer[256];
   
    for (i = 0; i < 256; i++) {
       buffer[i] = i;
    }
    
    VertexChunk1 *chunk1 = (VertexChunk1*)&buffer[10];
    VertexChunk2 *chunk2 = (VertexChunk2*)&buffer[10];
    
    printf("Are the chunk pointers equal? %i, %i\n", chunk1, chunk2);
    printf("Are the vertices pointers equal? %i, %i\n", &chunk1->vertices, chunk2->vertices);
    printf("Try to access chunk1.vertices: %f\n", (&chunk1->vertices)[2].z);
    printf("Try to access chunk2.vertices: %f\n", chunk2->vertices[2].z);
}
