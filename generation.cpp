#include "generation.h"
#include "struct.h"
#include "update_index_by_id.h"
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
    struct_item E;
    E.set_chto_eto(struct_chto_eto::object);
    E.get_set_object().igrok_mozhet_proyti = false;
    E.get_set_object().blokiruet_zrenie = true;
    E.get_set_xyzw().set_x(x,true);
    E.get_set_xyzw().set_y(y,true);
    E.get_set_xyzw().set_z(z,true);
    E.get_set_xyzw().set_w(w,true);
    E.get_set_object().textura = 'E';
    E.get_set_object().id = 0;
    long long key = make_key(x,y,z,w);
    state.item[key].push_back(E);
    }
    }
    }
}
}
std::unordered_set<long long> cells_to_index;

for(int skolko_raz_povtorit = 5; skolko_raz_povtorit > 0; --skolko_raz_povtorit){
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
}}}}}
long long key = make_key(x,y,z,w);
if(ryadom_E < 3){
auto it = state.item.find(key);
if(it != state.item.end()){
auto& vec = it->second;
for(int index = 0; index < vec.size();){
if(vec[index].get_chto_eto() == struct_chto_eto::object && vec[index].get_set_object().id == 0){
vec.erase(vec.begin()+index);
}
else{++index;}
}
if(vec.empty()){state.item.erase(it);}
}
}
else if(ryadom_E > 4){
if(state.item.count(key) == 0){
struct_item E;
    E.set_chto_eto(struct_chto_eto::object);
    E.get_set_object().igrok_mozhet_proyti = false;
    E.get_set_object().blokiruet_zrenie = true;
    E.get_set_xyzw().set_x(x,true);
    E.get_set_xyzw().set_y(y,true);
    E.get_set_xyzw().set_z(z,true);
    E.get_set_xyzw().set_w(w,true);
    E.get_set_object().textura = 'E';
    E.get_set_object().id = 0;
    state.item[key].push_back(E);
}
cells_to_index.insert(key);
}
else if(state.item.find(key) != state.item.end()){
cells_to_index.insert(key);
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
struct_item obj;
obj.set_chto_eto(struct_chto_eto::object);
obj.get_set_object().igrok_mozhet_proyti = true;
obj.get_set_object().blokiruet_zrenie = false;
obj.get_set_xyzw().set_x(svobodnye[index].get_x(),true);
obj.get_set_xyzw().set_y(svobodnye[index].get_y(),true);
obj.get_set_xyzw().set_z(svobodnye[index].get_z(),true);
obj.get_set_xyzw().set_w(svobodnye[index].get_w(),true);
obj.get_set_object().textura = ',';
obj.get_set_object().id = 1;
obj.get_set_object().set_pochva(true);
obj.get_set_object().set_resource(3);
long long key = make_key(svobodnye[index].get_x(),svobodnye[index].get_y(),svobodnye[index].get_z(),svobodnye[index].get_w());
state.item[key].push_back(obj);
state.pochva_keys.push_back(key);
cells_to_index.insert(key);
svobodnye[index] = svobodnye.back();
svobodnye.pop_back();
--skolko_nado;
}

for(long long k : cells_to_index){
index_cell(state,k);
}
state.loaded_chunks.insert(ckey);
}