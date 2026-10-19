#include "item.h"
std::vector<struct_item> type_item;

void start_create_type_item(){
struct_item obj;
obj.set_chto_eto(struct_chto_eto::object);
obj.get_set_object().id = type_item.size();
obj.get_set_object().igrok_mozhet_proyti = false;
obj.get_set_object().blokiruet_zrenie = true;
obj.get_set_object().textura = 'E';
type_item.push_back(obj);

struct_item pochva;
pochva.get_set_object().igrok_mozhet_proyti = true;
pochva.get_set_object().blokiruet_zrenie = false;
pochva.get_set_object().textura = ',';
pochva.get_set_object().id = type_item.size();
pochva.get_set_object().set_pochva(true);
pochva.get_set_object().set_resource(3,true);
}
void spawn_item(game_state& state, int x, int y, int z, int w, int id){

if(id < 0 || id >= type_item.size()){return;}
long long key = make_key(x,y,z,w);
state.item[key].push_back(type_item[id]);
}

