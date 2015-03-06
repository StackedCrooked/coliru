int[] ar_color = new int[80];
int[] ar_y = new int[80];
int[] ar_speed = new int[80];

void setup()
{
  size(800, 400);
  frameRate(60);
  noStroke();

  // create
  for (int i = 0; i < 80; i++)
  {
    makeOne(i);
  }
}

void draw()
{
  background(255, 255, 255);
  
  for (int i = 0; i < 80; i++)
  {
    // draw
    fill(ar_color[i]);
    ellipse(5 + i * 10, ar_y[i], 10, 10);
    
    // move
    ar_y[i] += ar_speed[i];
    if (ar_y[i] >= height)
    {
      // re-create
      makeOne(i);
    }
  }
}

void makeOne(int i)
{
  ar_color[i] = int(random(0, 0xffffff)) | 0xff000000;
  ar_y[i] = int(random(0, 10)) * 5;
  ar_speed[i] = int(random(1, 4)) * 5;
}
