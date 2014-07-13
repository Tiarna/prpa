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
