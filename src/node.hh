#ifndef NODE_HH
# define NODE_HH

# include "pixel.hh"

class Node
{
  public:

    Node(enum color c, int x, int y);
    Node(Pixel p, int x, int y);

    int distcarre(Pixel p);

    enum color getColor();

    void setColor(enum color c);

    void setX(int x);
    void setY(int y);

    int getX();
    int getY();

  private:
    enum color c_;
    int posX;
    int posY;
};

#endif
