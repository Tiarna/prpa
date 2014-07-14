#ifndef UPDATE_HH
# define UPDATE_HH

# include "node.hh"
# include <cmath>
# include <algorithm>

std::vector<Node> update(int width, int height, int bestfit,
                         Uint8 r, Uint8 g, Uint8 b,
                         std::vector<Node>& vec);

#endif /* !UPDATE_HH */
