float x_coord, y_coord;
float speed;
color col;

boolean isExist = false;

void setup()
{
  size(400, 200);
  noStroke();
}

void draw()
{
  final float accel = 0.5;
  final int radius = 10;
  final float alpha = -0.8;

  background(255);
  
  if (isExist)
  {
    fill(col);
    ellipse(x_coord, y_coord, radius * 2, radius * 2);

    if (y_coord + speed < height - radius)
    {
      y_coord += speed;
      speed += accel;
    }
    else
    {
      y_coord = height - radius;
      speed *= alpha;
    }
  }
}

void mouseClicked()
{
  x_coord = mouseX;
  y_coord = mouseY;
  speed = 0;
  col = int(random(0, 0xffffff)) | 0xff000000;
  isExist = true;
}