#include "generation.h"
#include "struct.h"
#include "update_index_by_id.h"
#include "item.h"
#include <random>
#include <chrono>

namespace{
std::uniform_int_distribution<int> random_(1,100);
}

void generate_chunk(game_state& state, int cx, int cy){
    long long ckey = make_ckey(chunk_of(cx),chunk_of(cy));
    auto it = state.loaded_chunks.find(ckey);
    if(it != state.loaded_chunks.end()){return;}

for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
    int spawn_chance_E = SPAWN_CHANCE_E;
    if(z >= 0 && z <= 1){spawn_chance_E += 5;}
    for(int x = cx; x < cx + chunk_size; ++x){
    for(int y = cy; y < cy + chunk_size; ++y){
    int sluchaino = random_(chislo);
    if(sluchaino <= spawn_chance_E){
    spawn_item(state,x,y,z,w,0);
    }
    }
    }
}
}

for(int skolko_raz_povtorit = SKOLKO_RAZ_POVTORIT; skolko_raz_povtorit > 0; --skolko_raz_povtorit){
for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){

int ryadom_E = 0;
for(int X = -1; X <= 1; ++X){
for(int Y = -1; Y <= 1; ++Y){
if(X == 0 && Y == 0){continue;}
long long key = make_key(x + X,y + Y,z,w);
if(state.item.count(key) > 0){
for(int index = 0; index < state.item[key].size(); ++index){
if(state.item[key][index].get_chto_eto() == struct_chto_eto::object && state.item[key][index].get_set_object().id == 0){
ryadom_E += 1; 
break;
}}}}}
    long long key = make_key(x,y,z,w);
auto it_cell = state.cells_to_index.find(key);
auto it = state.item.find(key);
if(ryadom_E < 3){
if(it != state.item.end()){
auto& vec = it->second;
for(int index = 0; index < vec.size();){
if(vec[index].get_chto_eto() == struct_chto_eto::object && vec[index].get_set_object().id == 0){
vec.erase(vec.begin()+index); break;
}
else{++index;}
}
if(vec.empty()){state.item.erase(it);
if(it_cell != state.cells_to_index.end()){state.cells_to_index.erase(key);}}
}
}
else if(ryadom_E > 4){
if(it == state.item.end()){
spawn_item(state,x,y,z,w,0);
}
}
}}}}}

std::vector<struct_xyzw> svobodnye;

for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){
long long key = make_key(x,y,z,w);
if(state.item.find(key) == state.item.end()){
struct_xyzw obj;
obj.set_x(x,true);
obj.set_y(y,true);
obj.set_z(z,true);
obj.set_w(w,true);
svobodnye.push_back(obj);}
}}}}

int skolko_nado = POCHVA_V_CHUNKE;
while(svobodnye.size() > 0 && skolko_nado > 0){
std::uniform_int_distribution<int> local(0,svobodnye.size()-1);
int index = local(chislo);
spawn_item(state,svobodnye[index].get_x(),svobodnye[index].get_y(),svobodnye[index].get_z(),svobodnye[index].get_w(),1);
svobodnye[index] = svobodnye.back();
svobodnye.pop_back();
--skolko_nado;
}
state.loaded_chunks.insert(ckey);
}