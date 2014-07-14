#ifndef UPDATE_HH
# define UPDATE_HH

# include "node.hh"
# include <cmath>

void update(int width, int height, int bestfit, Uint8 r, Uint8 g, Uint8 b,
            std::vector<Node>& map);

#endif /* !UPDATE_HH */
