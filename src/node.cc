#include "node.hh"

Node::Node(enum color c, int x, int y)
{
  posX= x;
  posY = y;
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
void Node::setX(int x)
{
  posX = x;
}

void Node::setY(int y)
{
  posY = y;
}

int Node::getX()
{
  return posX;
}

int Node::getY()
{
  return posY;
}
