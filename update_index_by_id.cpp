#include "update_index_by_id.h"

void index_cell(game_state& state, long long key){
    auto it = state.item.find(key);
    if(it == state.item.end() || it->second.empty()) { return; }

    int x = it->second[0].get_set_xyzw().get_x();
    int y = it->second[0].get_set_xyzw().get_y();
    long long ckey = make_ckey(chunk_of(x), chunk_of(y));

    for(auto& obj : it->second){
    int id = obj.get_set_object().id;
    if(id < 0){continue;}
    state.index_by_chunk[ckey][id].insert(key);
    }
}

void update_index_for_cell(game_state& state, long long key, int x, int y, int id){
auto it = state.item.find(key);

bool has = false;
if(it != state.item.end()){
for(auto& obj : it->second){
if(obj.get_set_object().id == id){has = true; break;}
}
}
if(has){return;}
long long ckey = make_ckey(chunk_of(x),chunk_of(y));
auto c_it = state.index_by_chunk.find(ckey);
if(c_it == state.index_by_chunk.end()){return;}

auto id_it = state.index_by_chunk[ckey].find(id);
if(id_it == state.index_by_chunk[ckey].end()){return;}

id_it->second.erase(key);

if(id_it->second.empty()) c_it->second.erase(id_it);
if(c_it->second.empty()) state.index_by_chunk.erase(c_it);
}