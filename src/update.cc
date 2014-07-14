# include "update.hh"


/*** neighbourhood function ***/

static float dist_nodes(int bestfit, int num_node, int width)
{
  int x_bestfit = bestfit % width;
  int y_bestfit = bestfit / width;

  int x_node = num_node % width;
  int y_node = num_node / width;

  int delta_x = x_node - x_bestfit;
  int delta_y = y_node - y_bestfit;

  return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

static float neighbourhood(int bestfit, int num_node, int width)
{
  float action_range = 1.0;

  return exp(- dist_nodes(bestfit, num_node, width)
             / (2 * pow(action_range, 2)));
}


/*** change functions ***/

static void change_color(Node& node, int R, int G, int B)
{
  node.setR(R);
  node.setG(G);
  node.setB(B);
}

static void change_bestfit(int bestfit, Uint8 r_px, Uint8 g_px, Uint8 b_px,
                           std::vector<Node>& vec)
{
  change_color(vec[bestfit], r_px, g_px, b_px);
}

static void change_neighbour(int bestfit, int num_node, Uint8 r_px, Uint8 g_px, Uint8 b_px,
                             int width, std::vector<Node>& vec)
{
  float learning_rate = 0.15;

  float red = vec[num_node].getR()
    + learning_rate * neighbourhood(bestfit, num_node, width)
    * (r_px -  vec[num_node].getR());

  float green = vec[num_node].getG()
    + learning_rate * neighbourhood(bestfit, num_node, width)
    * (g_px -  vec[num_node].getG());

  float blue = vec[num_node].getB()
    + learning_rate * neighbourhood(bestfit, num_node, width)
    * (b_px -  vec[num_node].getB());

  if (red < 0.f)
    red = 0;
  if (green < 0.f)
    green = 0;
  if (blue < 0.f)
    blue = 0;

  int r = round(red);
  int g = round(green);
  int b = round(blue);

  change_color(vec[num_node], r, g, b);
}


/*** update function ***/

std::vector<Node> update(int width, int height, int bestfit, Uint8 r, Uint8 g, Uint8 b,
    std::vector<Node>& vec)
{
  change_bestfit(bestfit, r, g, b, vec);

  // adjacent neighbours change
  if (bestfit % width != 0)
    change_neighbour(bestfit, bestfit - 1, r, g, b, width, vec);

  if (bestfit % width != (width - 1))
    change_neighbour(bestfit, bestfit + 1, r, g, b, width, vec);

  if (bestfit / height != 0)
    change_neighbour(bestfit, bestfit - width, r, g, b, width, vec);

  if (bestfit / height != (height - 1))
    change_neighbour(bestfit, bestfit + width, r, g, b, width, vec);

  // far neighbours change
  if ((bestfit % width != 0) && (bestfit / height != 0))
    change_neighbour(bestfit, bestfit - width - 1, r, g, b, width, vec);

  if ((bestfit % width != width - 1) && (bestfit / height != 0))
    change_neighbour(bestfit, bestfit - width + 1, r, g, b, width, vec);

  if ((bestfit % width != 0) && (bestfit / height != height - 1))
    change_neighbour(bestfit, bestfit + width - 1, r, g, b, width, vec);

  if ((bestfit % width != width - 1) && (bestfit / height != height - 1))
    change_neighbour(bestfit, bestfit + width + 1, r, g, b, width, vec);

  return vec;
}
