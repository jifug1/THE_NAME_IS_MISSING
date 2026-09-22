#include "update_index_by_id.h"

void index_cell(game_state& state, long long key){
        auto it = state.item.find(key);
    if(it == state.item.end() || it->second.empty()) { return; }

    int x = it->second[0].get_set_xyzw().get_x();
    int y = it->second[0].get_set_xyzw().get_y();
    long long ckey = make_ckey(chunk_of(x), chunk_of(y));

    state.index_by_chunk[ckey].insert(key);
}

void update_index_for_cell(game_state& state, long long key, int x, int y){
        auto it = state.item.find(key);
    if(it != state.item.end() && !it->second.empty()) { return; }

    long long ckey = make_ckey(chunk_of(x), chunk_of(y));
    auto idx_it = state.index_by_chunk.find(ckey);
    if(idx_it != state.index_by_chunk.end()){
        idx_it->second.erase(key);
    }
}