#include <map>
#include "node.hh"
#include <stdlib.h>
#include <vector>

std::vector<Node> init_node(std::vector<Pixel> vec, int width, int height)
{
  std::vector<Node> ret;
  bool test[16];
  for (int i = 0; i < 16; i++)
  {
    test[i] = true;
  }

  int count = 0;

  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      for (int k = 0; k < 16; k++)
      {
        if (test[k] && vec[i * j + j].getColor() ==  (enum color)k)
        {
          ret.push_back(Node((enum color)k, i, j));
          test[k] = false;
          count++;
          if (count == 15)
          {
            k = 42;
            i = width + 1;
            j = height + 1;
          }
        }
      }
    }
  }
  return ret;
}

std::vector<Pixel> init_pixels(int width, int height)
{
  std::vector<Pixel> ret;
  enum color col;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      col = (enum color)(rand() % 16);
      ret.push_back(Pixel(col));
    }
  }
  return ret;
}

int main(int argc, char** argv)
{
  argc = argc;
  argv = argv;
  std::vector<Pixel> vecPix = init_pixels(42, 42);
  std::vector<Node> vecNode = init_node(vecPix, 42, 42);
}
