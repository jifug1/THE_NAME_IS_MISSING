#include "struct.h"
const int chunk_size = 40;

long long make_key(int x, int y, int z, int w){
long long X = x + 10000;
long long Y = y + 10000;
long long Z = z + 1;
long long W = w + 1;
return (((X * 20001) + Y) * 3 + Z) * 3 + W;
}
int chunk_of(int position){
return (position >= 0) ? position / chunk_size :
-((-position) + chunk_size - 1) / chunk_size;
}
long long make_ckey(int x, int y){
long long X = x + 10000;
long long Y = y + 10000;
return (X * 20001) + Y;
}

bool proverka(game_state& state, const int x, const int y, const int z, const int w){
long long key = make_key(x,y,z,w);
if(state.item.count(key) > 0){
for(int index = 0; index < state.item[key].size(); ++index){
if(state.item[key][index].get_set_object().igrok_mozhet_proyti == false){
return false;
}
}
}
return true;
}

int game_state::get_igrok_x(){return igrok_x;}
int game_state::get_igrok_y(){return igrok_y;}
int game_state::get_igrok_z(){return igrok_z;}
int game_state::get_igrok_w(){return igrok_w;}

void game_state::set_igrok_x(int x, bool ustanovit){
    if(ustanovit == 1 && proverka(*this,x,igrok_y,igrok_z,igrok_w)){igrok_x = x;}
    else if(x <= 1 && x >= -1 && proverka(*this, igrok_x + x,igrok_y,igrok_z,igrok_w)){igrok_x += x;}
}
void game_state::set_igrok_y(int x, bool ustanovit){
    if(ustanovit == 1 && proverka(*this,igrok_x,x,igrok_z,igrok_w)){igrok_y = x;}
    else if(x <= 1 && x >= -1 && proverka(*this, igrok_x,igrok_y + x,igrok_z,igrok_w)){igrok_y += x;}
}void game_state::set_igrok_z(int x, bool ustanovit){
    if(ustanovit == 1 && proverka(*this,igrok_x,igrok_y,x,igrok_w)){igrok_z = x;}
    else if(x <= 1 && x >= -1 && x + igrok_z >= -1 && x + igrok_z <= 1 && proverka(*this, igrok_x,igrok_y,igrok_z + x,igrok_w)){igrok_z += x;}
}
void game_state::set_igrok_w(int x, bool ustanovit){
    if(ustanovit == 1 && proverka(*this,igrok_x,igrok_y,igrok_z,x)){igrok_w = x;}
    else if(x <= 1 && x >= -1 && x + igrok_w >= -1 && x + igrok_w <= 1 && proverka(*this, igrok_x,igrok_y,igrok_z,igrok_w + x)){igrok_w += x;}
}
struct_chto_eto struct_item::get_chto_eto(){return chto_eto;}
void struct_item::set_chto_eto(struct_chto_eto x){chto_eto = x;}

phase_state game_state::get_phase(){return phase;}
void game_state::set_phase(phase_state x){phase = x;}

int struct_xyzw::get_x(){return x;}
int struct_xyzw::get_y(){return y;}
int struct_xyzw::get_z(){return z;}
int struct_xyzw::get_w(){return w;}
void struct_xyzw::set_x(int chislo, bool ustanovit){
if(ustanovit){x = chislo;}
else{x += chislo;}
}
void struct_xyzw::set_y(int chislo, bool ustanovit){
if(ustanovit){y = chislo;}
else{y += chislo;}
}
void struct_xyzw::set_z(int chislo, bool ustanovit){
if(ustanovit){z = chislo;}
else{z += chislo;}
}
void struct_xyzw::set_w(int chislo, bool ustanovit){
if(ustanovit){w = chislo;}
else{w += chislo;}
}

struct_xyzw& struct_item::get_set_xyzw(){return xyzw;}
struct_object& struct_item::get_set_object(){return object;}
struct_xyzw& game_state::get_set_wasd(){return wasd;}
int game_state::get_wasd_timer() const{return wasd_timer;}
void game_state::set_wasd_timer(int x){wasd_timer = x;}
void game_state::update_teleport(){
if(wasd_timer == 0){
igrok_x = wasd.get_x();
igrok_y = wasd.get_y();
igrok_z = wasd.get_z();
igrok_w = wasd.get_w();
}
if(wasd_timer > -1){--wasd_timer;}
}