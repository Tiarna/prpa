#ifndef NODE_HH
# define NODE_HH

# include "pixel.hh"

class Node
{
  public:

    Node(int r, int g, int b);

    int distcarre(Pixel p);

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
