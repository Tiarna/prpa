# include "update.hh"

void change_color(Node& node, int R, int G, int B)
{
  node.setR(R);
  node.setG(G);
  node.setB(B);
}

static void change_bestfit(std::vector<Node>& vector, int bestfit,
    Uint32 current_pix)
{
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  SDL_GetRGB(current_pix, NULL, &r, &g, &b);

  change_color(vector[bestfit], r, g, b);
}

static void change_adj(std::vector<Node>& vector, int bestfit, int adj,
    Uint32 current_pix)
{
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  SDL_GetRGB(current_pix, NULL, &r, &g, &b);

  int red = vector[bestfit].getR()
    + 0.5 * (r -  vector[bestfit].getR());
  int green = vector[bestfit].getG()
    + 0.5 * (g -  vector[bestfit].getG());
  int blue = vector[bestfit].getB()
    + 0.5 * (b -  vector[bestfit].getB());

  change_color(vector[adj], red, green, blue);
}

static void change_far(std::vector<Node>& vector, int bestfit, int far,
    Uint32 current_pix)
{
  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;
  SDL_GetRGB(current_pix, NULL, &r, &g, &b);

  int red = vector[bestfit].getR()
    + 0.25 * (r -  vector[bestfit].getR());
  int green = vector[bestfit].getG()
    + 0.25 * (g -  vector[bestfit].getG());
  int blue = vector[bestfit].getB()
    + 0.25 * (b -  vector[bestfit].getB());

  change_color(vector[far], red, green, blue);
}


/*** update function ***/

void update(int width, int height, int bestfit, Uint32 current_pix,
    std::vector<Node>& map)
{
  change_bestfit(map, bestfit, current_pix);

  /* adjacent neighbours change */
  if (bestfit % width != 0)
    change_adj(map, bestfit, bestfit - 1, current_pix);

  if (bestfit % width != (width - 1))
    change_adj(map, bestfit, bestfit + 1, current_pix);

  if (bestfit / height != 0)
    change_adj(map, bestfit, bestfit - width, current_pix);

  if (bestfit / height != (height - 1))
    change_adj(map, bestfit, bestfit + width, current_pix);

  /* far neighbours change */
  if ((bestfit % width != 0) && (bestfit / height != 0))
    change_far(map, bestfit, bestfit - width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != 0))
    change_far(map, bestfit, bestfit - width + 1, current_pix);

  if ((bestfit % width != 0) && (bestfit / height != height - 1))
    change_far(map, bestfit, bestfit + width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != height - 1))
    change_far(map, bestfit, bestfit + width + 1, current_pix);

}
