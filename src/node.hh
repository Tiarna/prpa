#ifndef NODE_HH
# define NODE_HH

# include <stdlib.h>
# include <vector>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

class Node
{
  public:

    Node(int r, int g, int b);

    int dist2(Uint8 r, Uint8 g, Uint8 b);

    Uint8 getR();
    Uint8 getG();
    Uint8 getB();

    void setR(Uint8 r);
    void setG(Uint8 g);
    void setB(Uint8 b);

  private:
    Uint8 R;
    Uint8 G;
    Uint8 B;
};

#endif
