#include "pixel.hh"

Pixel::Pixel(enum color c)
{
  c_ = c;
}

enum color Pixel::getColor()
{
  return c_;
}

void Pixel::setColor(enum color c)
{
  c_ = c;
}
