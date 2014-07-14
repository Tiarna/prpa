#include "random_suite.hh"

static std::vector<int>
random_uniform_suite(int px_min, int px_max, int size)
{
  std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(px_min, px_max);
  std::vector<int> suite;

  for (int i = 0; i <= size - 1; i++)
    suite.push_back(distribution(generator));

  // repetitions elimination
  auto it = suite.begin();
  while (it != suite.end())
  {
    while (std::find(it + 1, suite.end(), *it) != suite.end())
      *it = (*it + 1) % px_max;

    it++;
  }

  return suite;
}

/** regular step : inutil **/
/*
static std::vector<int>
random_uniform_suite(int inutil, int px_nb, int sample_nb)
{
  inutil = inutil;
  px_nb++;

  int px = 0;
  std::vector<int> suite;
  int count = 0;

  while ((px < px_nb) && (count <= sample_nb))
  {
    suite.push_back(px);
    px = px + (px_nb / sample_nb);
    count++;
  }

  return suite;
}
*/

std::vector<int> get_random_suite(int px_nb, int sample_nb)
{
  if (sample_nb > px_nb)
  {
    std::cout << "Too much samples. Only " << px_nb
      << " samples will be extracted" << std::endl;

    sample_nb = px_nb;
  }

  std::vector<int> suite = random_uniform_suite(0, px_nb - 1, sample_nb);

  return suite;
}
