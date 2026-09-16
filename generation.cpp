#include "generation.h"
#include "struct.h"
#include <random>
#include <chrono>

namespace{
std::mt19937 chislo(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> random_(1,100);
}

void generation_pishery(game_state& state){
for(int w = -1; w <= 1; ++w){
for(int z = -1; z <= 1; ++z){
    for(int x = -100; x <= 100; ++x){
    for(int y = -100; y <= 100; ++y){
    int sluchaino = random_(chislo);
    if(sluchaino <= 45){
    struct_item stena;
    stena.set_chto_eto(struct_chto_eto::object);
    stena.get_set_object().igrok_mozhet_proyti = false;
    stena.get_set_xyzw().set_x(x,true);
    stena.get_set_xyzw().set_y(y,true);
    stena.get_set_xyzw().set_z(z,true);
    stena.get_set_xyzw().set_w(w,true);
    stena.get_set_object().textura = "E";
    stena.get_set_object().id = 0;
    long long key = make_key(x,y,z,w);
    state.item[key].push_back(stena);
    }
    }
    }
}
}
for(int skolko_raz_povtorit = 5; skolko_raz_povtorit > 0; --skolko_raz_povtorit){
for(int w = -1; w <= 1; ++w){
for(int z = -1; z <= 1; ++z){
for(int x = -100; x <= 100; ++x){
for(int y = -100; y <= 100; ++y){

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
    stena.get_set_object().textura = "E";
    stena.get_set_object().id = 0;
    state.item[key].push_back(stena);
}
}
}}}}}
}
