#include "pixel.hh"


Pixel(int r, int g, int b)
{
  if (r > 255)
    R = 255;
  else if (r < 0)
    R = 0;
  else
    R = r;

  if (g > 255)
    G = 255;
  else if (g < 0)
    G = 0;
  else
    G = g;

  if (b > 255)
    B = 255;
  else if (b < 0)
    B = 0;
  else
    B = b;
}

int getR()
{
  return R;
}

int getG();
{
  return G;
}

int getB()
{
  return B
}

void setR(int r)
{
  if (r > 255)
    R = 255;
  else if (r < 0)
    R = 0;
  else
    R = r;
}

void setG(int g)
{
  if (g > 255)
    G = 255;
  else if (g < 0)
    G = 0;
  else
    G = g;
}

void setB(int b)
{
  if (b > 255)
    B = 255;
  else if (b < 0)
    B = 0;
  else
    B = b;
}
