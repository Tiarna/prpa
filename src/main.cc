#include "main.hh"

/*Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
  int bpp = surface->format->BytesPerPixel;
   Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

  switch(bpp) {
    case 1:
      return *p;
      break;

    case 2:
      return *(Uint16 *)p;
      break;

    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        return p[0] << 16 | p[1] << 8 | p[2];
      else
        return p[0] | p[1] << 8 | p[2] << 16;
      break;

    case 4:
      return *(Uint32 *)p;
      break;

    default:
      return 0;
  }
}*/

unsigned int getpixel(SDL_Surface *s, int x, int y)
{
  return ((unsigned int*)s->pixels)[y*(s->pitch/sizeof(unsigned int)) + x];
}


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

void my_pause()
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
    //*pix[dim] = {NULL};
    pix[i] = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
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
  my_pause();
  for (int i = 0 ; i < width * height; i++)
    SDL_FreeSurface(pix[i]);
  SDL_Quit();
}

int search_closer(Uint8 r, Uint8 g, Uint8 b, std::vector<Node> vec)
{
  int min = 196000;
  int tmp;
  int pos;
  for (unsigned int i = 0; i < vec.size(); i++)
  {
    tmp = vec[i].dist2(r, g, b);
    if (min > tmp)
    {
      min = tmp;
      pos = i;
    }
  }
  return pos;
}

std::vector<Node> calculate_seq(char* file, std::vector<Node> vec, int width,
    int height, std::vector<int> vecint)
{
  //  std::cout << "DEBUG main.cc: calculate: begin of fct" << std::endl;

  SDL_Surface *img = NULL;
  SDL_Init(SDL_INIT_VIDEO);
  img = SDL_LoadBMP(file);

  //  std::cout << "DEBUG main.cc: calculate: after image loading"
  //            << ". Img vals " << img << std::endl;

  Uint32 current_pix = 0;

  Uint8 r = 0;
  Uint8 g = 0;
  Uint8 b = 0;

  int bestfit;

  std::vector<Node> ret = vec;
  double par_time;
  {
    timer t(par_time);

    for (unsigned int i = 0; i < vecint.size(); i++)
    {
      current_pix = getpixel(img, vecint[i] / height, vecint[i] % height);
      SDL_GetRGB(current_pix, img->format, &r, &g, &b);
      bestfit = search_closer(r, g, b, vec);
      ret = update(width, height, bestfit, r, g, b, vec);
    }
  }
  std::cout << "Sequential time: \t" << par_time << std::endl;

  return ret;
}

class apply_par
{
  public:
    void operator()(const tbb::blocked_range<size_t>& rank) const
    {
      Uint32 current_pix = 0;

      Uint8 r = 0;
      Uint8 g = 0;
      Uint8 b = 0;
      int bestfit;

      for(size_t i = rank.begin(); i != rank.end(); i++)
      {
        std::vector<Node> t = vec;
        current_pix = getpixel(img, vecint[i] / height, vecint[i] % height);
        SDL_GetRGB(current_pix, img->format, &r, &g, &b);
        bestfit = search_closer(r, g, b, vec);
        ret = update(width, height, bestfit, r, g, b, t);
      }
    }

    apply_par(char* file, std::vector<Node>& v, int w, int h, int it, std::vector<int> vt)
      :vec(v), width(w), height(h), iteration_nb(it), vecint(vt), ret(v)
    {
      SDL_Init(SDL_INIT_VIDEO);
      img = SDL_LoadBMP(file);
    }

    std::vector<Node> getvec()
    {
      return ret;
    }

  private:
    SDL_Surface *img = NULL;
    std::vector<int> vecint;

    char* file;
    std::vector<Node>& vec;
    int width;
    int height;
    int iteration_nb;
    std::vector<Node>& ret;
};

std::vector<Node> calculate_par(char* file, std::vector<Node> vec, int width,
    int height, int iteration_nb, std::vector<int> vecint)
{
  apply_par app = apply_par(file, vec, width, height, iteration_nb, vecint);
  double par_time;
  {
    timer t(par_time);
    tbb::parallel_for(tbb::blocked_range<size_t>(0, vecint.size()), app);
  }
  std::cout << "Parallel time: \t" << par_time << std::endl;

  return app.getvec();
}
int main(int argc, char** argv)
{
  if (argc != 5)
  {
    std::cout << "using: Filename dimx dimy nb_iteration" << std::endl;
    return 1;
  }

  int width = atoi(argv[2]);

  int height = atoi(argv[3]);

  int iteration_nb = atoi(argv[4]);

  std::vector<Node> vecNode_seq = init_node(width, height);
  std::vector<Node> vecNode_par = vecNode_seq;
  std::vector<int> vecint = get_random_suite(width * height, iteration_nb);

  vecNode_seq = calculate_seq(argv[1], vecNode_seq, width, height, vecint);

  display(vecNode_seq, width, height);

  vecNode_par = calculate_par(argv[1], vecNode_par, width, height, iteration_nb, vecint);

  display(vecNode_par, width, height);
}
