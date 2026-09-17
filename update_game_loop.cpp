#include "update_game_loop.h"
#include "generation.h"

void chunk_proverka(game_state& state){
int px = state.get_igrok_x();
int py = state.get_igrok_y();
long long ckey = make_ckey(chunk_of(px),chunk_of(py));
auto it = state.loaded_chunks.find(ckey);
if(it != state.loaded_chunks.end()){return;}
int cx0 = chunk_of(px - (chunk_size * 2));
int cx1 = chunk_of(px + (chunk_size * 2));
int cy0 = chunk_of(py - (chunk_size * 2));
int cy1 = chunk_of(py + (chunk_size * 2));
for(int cx = cx0; cx <= cx1; ++cx){
for(int cy = cy0; cy <= cy1; ++cy){
generate_chunk(state,cx * chunk_size,cy * chunk_size);
}
}
}
void update(game_state& state){
chunk_proverka(state);
state.update_teleport();
}