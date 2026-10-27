#ifndef ITEM_H
#define ITEM_H
#include "struct.h"

void start_create_type_item();
void spawn_item(game_state& state, int x, int y, int z, int w, int id);
extern std::vector<struct_item> type_item;

#endif