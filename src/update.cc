# include "update.hh"
#include <iostream>

/*** neighbourhood function ***/

static float dist_nodes(int bestfit, int num_node, int width)
{
  int x_bestfit = bestfit % width;
  int y_bestfit = bestfit / width;

  int x_node = num_node % width;
  int y_node = num_node / width;

  int delta_x = x_node - x_bestfit;
  int delta_y = y_node - y_bestfit;

  return delta_x * delta_x + delta_y * delta_y;
}

static float neighbourhood(int bestfit, int num_node, int width, int height)
{
  float action_range = (width + height) / 4;

  return exp(- dist_nodes(bestfit, num_node, width)
             / (2 * pow(action_range, 2)));
}


/*** change functions ***/

static void change_color(Node& node, Uint8 R, Uint8 G, Uint8 B)
{
  node.setR(R);
  node.setG(G);
  node.setB(B);
}

static void update_node(int bestfit, int num_node,
                        Uint8 r_px, Uint8 g_px, Uint8 b_px,
                        int width, int height, std::vector<Node>& vec)
{
  float learning_rate = 0.2;

  Uint8 red = vec[num_node].getR()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (r_px -  vec[num_node].getR());

  Uint8 green = vec[num_node].getG()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (g_px -  vec[num_node].getG());

  Uint8 blue = vec[num_node].getB()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (b_px -  vec[num_node].getB());

  if (red < 0.f)
    red = 0;
  if (green < 0.f)
    green = 0;
  if (blue < 0.f)
    blue = 0;

  change_color(vec[num_node], red, green, blue);
}


/*** update function ***/

std::vector<Node> update(int width, int height, int bestfit,
                         Uint8 r, Uint8 g, Uint8 b,
                         std::vector<Node>& vec)
{
  for (int num_node = 0; num_node < vec.size(); num_node++)
    update_node(bestfit, num_node, r, g, b, width, height, vec);

  return vec;
}
