#ifndef PIXEL_HH
# define PIXEL_HH

enum color
{
  white = {255, 255, 255},
  black = {0, 0, 0},

  red = {255, 0, 0},
  green = {0, 255, 0},
  bluemarine = {0, 0, 255},
  yellow = {255, 255, 0},
  purple = {255, 0, 255},
  cyan = {0, 255, 255},

  orange = {255, 127 0},
  magenta = {255, 0, 127},
  greenpale = {0, 255, 127},
  greenclare = {127, 255, 0},
  darkpurple = {127, 0, 255},
  blue = {0, 127, 255},

  grey = {127, 127, 127}
};

class Pixel
{
  public:

    Pixel(enum color c);

    enum color getColor();

    void setColor(enum color c);

  private:

    enum color c_;
};

#endif
