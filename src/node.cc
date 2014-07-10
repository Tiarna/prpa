#include "node.hh"

Node(enum color c, int x, int y)
{
  posX= x;
  PosY = y;
  c_ = c;
}

enum color Node::getColor()
{
  return c_;
}

void Node::setColor(enum color c)
{
  c_ = c;
}
void setX(int x)
{
  posX = x;
}

void setY(int y)
{
  posY = y;
}

int getX()
{
  return x;
}

int getY()
{
  return y;
}
