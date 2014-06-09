

int main() {
union
{
  struct
  {
    float x, y, z, w;
  };
  struct
  {
    float r, g, b, a;
  };

  float v[4];
};    
    
}
