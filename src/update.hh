#ifndef UPDATE_HH
# define UPDATE_HH

# include "node.hh"

void update(int width, int height, int bestfit, Uint32 current_pix,
            std::vector<Node>& map);

#endif /* !UPDATE_HH */
