# include "update.hh"


/*** neighbourhood function ***/

static float dist_nodes(int bestfit, int num_node, int width, int height)
{
  int x_bestfit = bestfit % width;
  int y_bestfit = bestfit / width;

  int x_node = num_node % width;
  int y_node = num_node / width;

  int delta_x = x_node - x_bestfit;
  int delta_y = y_node - y_bestfit;

  return sqrt(pow(delta_x, 2) + pow(delta_y, 2));
}

static float neighbourhood(int bestfit, int num_node, int width, int height)
{
  float action_range = 1.0;

  return exp(- dist_nodes(bestfit, num_node, width, height)
             / (2 * pow(action_range, 2)));
}


/*** change functions ***/

static void change_color(Node& node, int R, int G, int B)
{
  node.setR(R);
  node.setG(G);
  node.setB(B);
}

static void change_bestfit(int bestfit, Uint32 current_pix)
{
  change_color(vector[bestfit], getr(current_pix), getg(current_pix),
               getb(current_pix));
}

static void change_neighbour(int bestfit, int num_node, Uint32 current_pix,
                             int width, int height)
{
  float learning_rate = 0.15;

  float red = vector[num_node].getR()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (getr(current_pix) -  vector[num_node].getR());

  float green = vector[num_node].getG()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (getg(current_pix) -  vector[num_node].getG());

  float blue = vector[num_node].getB()
    + learning_rate * neighbourhood(bestfit, num_node, width, height)
    * (getb(current_pix) -  vector[num_node].getB());

  (red < 0.f) ? 0.f : red;
  (green < 0.f) ? 0.f : green;
  (blue < 0.f) ? 0.f : blue;

  int r = round(red);
  int g = round(green);
  int b = round(blue);

  change_color(vector[num_node], r, g, b);
}


/*** update function ***/

void update(int width, int height, int bestfit, Uint32 current_pix,
    std::vector<Node>& map)
{
  change_bestfit(bestfit, current_pix);

  // adjacent neighbours change
  if (bestfit % width != 0)
    change_neighbour(bestfit, bestfit - 1, current_pix);

  if (bestfit % width != (width - 1))
    change_neighbour(bestfit, bestfit + 1, current_pix);

  if (bestfit / height != 0)
    change_neighbour(bestfit, bestfit - width, current_pix);

  if (bestfit / height != (height - 1))
    change_neighbour(bestfit, bestfit + width, current_pix);

  // far neighbours change
  if ((bestfit % width != 0) && (bestfit / height != 0))
    change_neighbour(bestfit, bestfit - width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != 0))
    change_neighbour(bestfit, bestfit - width + 1, current_pix);

  if ((bestfit % width != 0) && (bestfit / height != height - 1))
    change_neighbour(bestfit, bestfit + width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != height - 1))
    change_neighbour(bestfit, bestfit + width + 1, current_pix);

}
