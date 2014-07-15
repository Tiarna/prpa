#ifndef UPDATE_HH
# define UPDATE_HH

# include "node.hh"
# include <cmath>
# include <algorithm>

#ifndef M_PI
# define M_PI 3.14159
#endif


std::vector<Node> update(int width, int height, int bestfit,
                         Uint8 r, Uint8 g, Uint8 b,
                         std::vector<Node>& vec);

#endif /* !UPDATE_HH */
