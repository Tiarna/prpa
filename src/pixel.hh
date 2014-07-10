#ifndef PIXEL_HH
# define PIXEL_HH

class Pixel
{
  public:

    Pixel(int r, int g, int b);

    int getR();
    int getG();
    int getB();

    void setR(int r);
    void setG(int g);
    void setB(int b);

  private:
    int R;
    int G;
    int B;
};

#endif
