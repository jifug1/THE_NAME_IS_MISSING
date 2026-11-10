#include "struct.h"
#include "update_index_by_id.h"
std::mt19937 chislo(std::chrono::steady_clock::now().time_since_epoch().count());
char VOID = '.';
char THE_UNKNOWN = ' ';
long long make_key(int x, int y, int z, int w){
long long X = x + 10000;
long long Y = y + 10000;
long long Z = z - MIN_Z;
long long W = w - MIN_W;
return (((X * 20001) + Y) * (MAX_Z - MIN_Z + 1) + Z) * (MAX_W - MIN_W + 1) + W;
}

void skushat_nyamku(game_state& state, struct_item& igrok){
long long key = make_key(igrok.get_set_xyzw().get_x(),igrok.get_set_xyzw().get_y(),igrok.get_set_xyzw().get_z(),igrok.get_set_xyzw().get_w());
auto it = state.item.find(key);
if(it == state.item.end()){return;}
for(int i = 0; i < it->second.size(); ++i){
if(it->second[i].get_set_object().sytost > 0 && it->second[i].get_chto_eto() == struct_chto_eto::object){igrok.get_set_entity().set_sytost(it->second[i].get_set_object().sytost,false);
int id = it->second[i].get_set_object().id;
it->second[i] = it->second.back();
it->second.pop_back();
update_index_for_cell(state,key,igrok.get_set_xyzw().get_x(),igrok.get_set_xyzw().get_y(),id);
if(it->second.empty()){state.item.erase(it);}
break;
}
}
}

int chunk_of(int position){
return (position >= 0) ? position / chunk_size :
-((-position) + chunk_size - 1) / chunk_size;
}
long long make_ckey(int x, int y){
long long X = x + 250;
long long Y = y + 250;
return (X * 501) + Y;
}

bool proverka(game_state& state, const int x, const int y, const int z, const int w){
if(!((z >= MIN_Z && z <= MAX_Z) && (w >= MIN_W && w <= MAX_W))){return false;}
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
struct_xyzw& struct_entity::get_set_mesto_tseli(){return mesto_tseli;}
struct_entity& struct_item::get_set_entity(){return entity;}
int struct_entity::get_id_tseli(){return id_tseli;}
void struct_entity::set_id_tseli(int x){id_tseli = x;}
int struct_entity::get_sytost(){return sytost;}
void struct_entity::set_sytost(int x, bool ustanovit){if(ustanovit){sytost = x;}else{sytost += x;}}

void struct_entity::update_sytost(){
--sytost;
++how_much_was_spent;
if(sytost <= 0){mertv = true;}
}

void struct_item::update_sytost_obj_sytost(){
get_set_object().sytost = get_set_entity().get_sytost();
}

bool struct_entity::get_mertv(){return mertv;}
std::vector<struct_xyzw>& struct_entity::get_set_marshrut(){return marshrut;}
int struct_entity::get_counter(){return counter;}
void struct_entity::set_counter(int x,bool ustanovit){if(ustanovit){counter = x;}else{counter += x;}}
long long struct_entity::get_target_key(){return target_key;}
void struct_entity::set_target_key(long long x){target_key = x;}
int struct_entity::get_target_index(){return target_index;}
void struct_entity::set_target_index(int x){target_index = x;}

bool struct_object::get_pochva(){return pochva;}
void struct_object::set_pochva(bool x){pochva = x;}
int struct_object::get_resource(){return resource;}
void struct_object::set_resource(int x, bool ustanovit){if(ustanovit){resource = x;}else{resource += x;}}

void game_state::update_propustit_vvod(){
if(propustit_vvod_timer > 0){--propustit_vvod_timer;}
}
int game_state::get_propustit_vvod_timer(){return propustit_vvod_timer;}
void game_state::set_propustit_vvod_timer(int x){propustit_vvod_timer += x;}

int struct_object::get_id_of_the_item_that_will_be_spawned(){return id_of_the_item_that_will_be_spawned;}
void struct_object::set_id_of_the_item_that_will_be_spawned(int x){id_of_the_item_that_will_be_spawned = x;}

struct_what_it_eats struct_entity::get_what_it_eats(){return what_it_eats;}
int struct_entity::get_how_much_was_spent(){return how_much_was_spent;}