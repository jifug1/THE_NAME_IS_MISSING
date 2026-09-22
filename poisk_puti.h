#ifndef POISK_PUTI_H
#define POISK_PUTI_H
#include "struct.h"
#include <vector>

std::vector<struct_xyzw> nayti_put(game_state& state, struct_item& e, struct_xyzw& A, struct_xyzw& B);
int heuristic(struct_xyzw& a, struct_xyzw& b);

#endif