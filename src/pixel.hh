#ifndef PIXEL_HH
# define PIXEL_HH

enum color
{
  White = 0xFFFFFF,
  Silver = 0xC0C0C0,
  Gray = 0x808080,
  Black = 0x000000,
  Red = 0xFF0000,
  Maroon = 0x800000,
  Yellow = 0xFFFF00,
  Olive = 0x808000,
  Lime = 0x00FF00,
  Green = 0x008000,
  Aqua = 0x00FFFF,
  Teal = 0x008080,
  Blue = 0x0000FF,
  Navy = 0x000080,
  Fuchsia = 0xFF00FF,
  Purple = 0x800080
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
