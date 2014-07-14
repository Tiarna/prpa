# include "update.hh"

void change_color(Node& node, int R, int G, int B)
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

static void change_adj(int bestfit, int adj, Uint32 current_pix)
{
  int red = vector[bestfit].getR()
    + 0.5 * (getr(current_pix) -  vector[bestfit].getR());
  int green = vector[bestfit].getG()
    + 0.5 * (getg(current_pix) -  vector[bestfit].getG());
  int blue = vector[bestfit].getB()
    + 0.5 * (getb(current_pix) -  vector[bestfit].getB());

  change_color(vector[adj], red, green, blue);
}

static void change_far(int bestfit, int far, Uint32 current_pix)
{
  int red = vector[bestfit].getR()
    + 0.25 * (getr(current_pix) -  vector[bestfit].getR());
  int green = vector[bestfit].getG()
    + 0.25 * (getg(current_pix) -  vector[bestfit].getG());
  int blue = vector[bestfit].getB()
    + 0.25 * (getb(current_pix) -  vector[bestfit].getB());

  change_color(vector[far], red, green, blue);
}


/*** update function ***/

void update(int width, int height, int bestfit, Uint32 current_pix,
    std::vector<Node>& map)
{
  change_bestfit(bestfit, current_pix);

  /* adjacent neighbours change */
  if (bestfit % width != 0)
    change_adj(bestfit, bestfit - 1, current_pix);

  if (bestfit % width != (width - 1))
    change_adj(bestfit, bestfit + 1, current_pix);

  if (bestfit / height != 0)
    change_adj(bestfit, bestfit - width, current_pix);

  if (bestfit / height != (height - 1))
    change_adj(bestfit, bestfit + width, current_pix);

  /* far neighbours change */
  if ((bestfit % width != 0) && (bestfit / height != 0))
    change_far(bestfit, bestfit - width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != 0))
    change_far(bestfit, bestfit - width + 1, current_pix);

  if ((bestfit % width != 0) && (bestfit / height != height - 1))
    change_far(bestfit, bestfit + width - 1, current_pix);

  if ((bestfit % width != width - 1) && (bestfit / height != height - 1))
    change_far(bestfit, bestfit + width + 1, current_pix);

}
