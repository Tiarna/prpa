#include "node.hh"

Node::Node(int r, int g, int b)
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

int Node::dist2(Uint8 r, Uint8 g, Uint8 b)
{
  int rR = ((int)r - (int)R) * ((int)r - (int)R);
  int gG = ((int)g - (int)G) * ((int)g - (int)G);
  int bB = ((int)b - (int)B) * ((int)b -(int) B);
  return rR + gG + bB;
}

Uint8 Node::getR()
{
  return R;
}

Uint8 Node::getG()
{
  return G;
}

Uint8 Node::getB()
{
  return B;
}

void Node::setR(Uint8 r)
{
  /*if (r > 255)
    R = 255;
  else if (r < 0)
    R = 0;
  else*/
    R = r;
}

void Node::setG(Uint8 g)
{
  /*if (g > 255)
    G = 255;
  else if (g < 0)
    G = 0;
  else*/
    G = g;
}

void Node::setB(Uint8 b)
{
  /*if (b > 255)
    B = 255;
  else if (b < 0)
    B = 0;
  else*/
    B = b;
}
