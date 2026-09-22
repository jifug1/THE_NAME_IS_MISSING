#include "generation.h"
#include "struct.h"
#include "update_index_by_id.h"
#include <random>
#include <chrono>

namespace{
std::mt19937 chislo(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> random_(1,100);
}

void generate_chunk(game_state& state, int cx, int cy){
    long long ckey = make_ckey(chunk_of(cx),chunk_of(cy));
    auto it = state.loaded_chunks.find(ckey);
    if(it != state.loaded_chunks.end()){return;}
for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
    for(int x = cx; x < cx + chunk_size; ++x){
    for(int y = cy; y < cy + chunk_size; ++y){
    int sluchaino = random_(chislo);
    if(sluchaino <= 45){
    struct_item stena;
    stena.set_chto_eto(struct_chto_eto::object);
    stena.get_set_object().igrok_mozhet_proyti = false;
    stena.get_set_xyzw().set_x(x,true);
    stena.get_set_xyzw().set_y(y,true);
    stena.get_set_xyzw().set_z(z,true);
    stena.get_set_xyzw().set_w(w,true);
    stena.get_set_object().textura = 'E';
    stena.get_set_object().id = 0;
    long long key = make_key(x,y,z,w);
    state.item[key].push_back(stena);
    }
    }
    }
}
}
for(int skolko_raz_povtorit = 5; skolko_raz_povtorit > 0; --skolko_raz_povtorit){
for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){

int ryadom_sten = 0;
for(int X = -1; X <= 1; ++X){
for(int Y = -1; Y <= 1; ++Y){
if(X == 0 && Y == 0){continue;}
long long key = make_key(x + X,y + Y,z,w);
if(state.item.count(key) > 0){
for(int index = 0; index < state.item[key].size(); ++index){
if(state.item[key][index].get_chto_eto() == struct_chto_eto::object && state.item[key][index].get_set_object().id == 0){
ryadom_sten += 1;
}}}}}
long long key = make_key(x,y,z,w);
if(ryadom_sten < 3){
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
else if(ryadom_sten > 4){
if(state.item.count(key) == 0){
struct_item stena;
    stena.set_chto_eto(struct_chto_eto::object);
    stena.get_set_object().igrok_mozhet_proyti = false;
    stena.get_set_xyzw().set_x(x,true);
    stena.get_set_xyzw().set_y(y,true);
    stena.get_set_xyzw().set_z(z,true);
    stena.get_set_xyzw().set_w(w,true);
    stena.get_set_object().textura = 'E';
    stena.get_set_object().id = 0;
    state.item[key].push_back(stena);
}
}
}}}}}


for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){
    index_cell(state, make_key(x,y,z,w));
}}}}

int skolko_nado = nuzhno_travy_v_chunke;
while(skolko_nado > 0){
for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){
long long key = make_key(x,y,z,w);
auto it = state.item.find(key);
if(it == state.item.end() && skolko_nado > 0){
int sluchaino = random_(chislo);
if(sluchaino <= 10){
struct_item trava;
trava.set_chto_eto(struct_chto_eto::object);
trava.get_set_object().igrok_mozhet_proyti = true;
trava.get_set_xyzw().set_x(x,true);
trava.get_set_xyzw().set_y(y,true);
trava.get_set_xyzw().set_z(z,true);
trava.get_set_xyzw().set_w(w,true);
trava.get_set_object().textura = 'W';
trava.get_set_object().id = 1;
trava.get_set_object().sytost = 5;
state.item[key].push_back(trava);
index_cell(state,key);
--skolko_nado;
}}}}}}}
skolko_nado = X_v_chunke;
while(skolko_nado > 0){

for(int w = MIN_W; w <= MAX_W; ++w){
for(int z = MIN_Z; z <= MAX_Z; ++z){
for(int x = cx; x < cx + chunk_size; ++x){
for(int y = cy; y < cy + chunk_size; ++y){
long long key = make_key(x,y,z,w);
auto it = state.item.find(key);
if(it == state.item.end() && skolko_nado > 0){
int sluchaino = random_(chislo);
if(sluchaino <= 1){
std::uniform_int_distribution<int> local(30,80);
int sluchaino = local(chislo);
struct_item X;
X.set_chto_eto(struct_chto_eto::entity);
X.get_set_object().igrok_mozhet_proyti = true;
X.get_set_xyzw().set_x(x,true);
X.get_set_xyzw().set_y(y,true);
X.get_set_xyzw().set_z(z,true);
X.get_set_xyzw().set_w(w,true);
X.get_set_object().textura = 'X';
X.get_set_object().id = 2;
X.get_set_entity().set_kak_chasto_spat(sluchaino);
X.get_set_entity().set_id_tseli(1);
X.get_set_entity().set_bodrost(sluchaino);
X.get_set_entity().set_spit(0);
X.get_set_entity().set_sytost(20);
state.item[key].push_back(X);
state.entity_keys.push_back(key);
index_cell(state,key);
--skolko_nado;
}}}}}}}
state.loaded_chunks.insert(ckey);
}