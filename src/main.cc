#include "main.hh"

std::vector<Node> init_node(int width, int height)
{
  std::vector<Node> ret;
  int r, g, b;
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      r = rand() % 256;
      g = rand() % 256;
      b = rand() % 256;
      ret.push_back(Node(r, g, b));
    }
  }
  return ret;
}

void pause()
{
  int continuer = 1;
  SDL_Event event;

  while (continuer)
  {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
      case SDL_QUIT:
        continuer = 0;
    }
  }
}

void display(std::vector<Node> vec, int width, int height)
{
  vec = vec;
  SDL_Surface *ecran = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  ecran = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);

  SDL_Rect position;
  position.x = 0;
  position.y = 0;

  int dim = height * width;

  SDL_Surface *pix[dim];

  for (int i = 0; i < width * height; i++)
  {
    *pix[dim] = {NULL};
    pix[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
  }

  SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

  for (int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      position.x = i;
      position.y = j;
      SDL_FillRect(pix[i * j + j], NULL, SDL_MapRGB(ecran->format, vec[i * j + j].getR(), vec[i * j + j].getG(), vec[i * j + j].getB()));
      SDL_BlitSurface(pix[i * j + j], NULL, ecran, &position);
    }
  }
  SDL_Flip(ecran);
  pause();
  for (int i = 0 ; i < width * height; i++) // N'oubliez pas de libérer les 256 surfaces
            SDL_FreeSurface(pix[i]);
  SDL_Quit();
}

int main(int argc, char** argv)
{
  argc = argc;
  argv = argv;
  std::vector<Node> vecNode = init_node(100, 100);
  display(vecNode, 100, 100);
}
