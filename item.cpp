#include "item.h"
std::vector<struct_item> type_item;

void start_create_type_item(){
type_item.clear();
struct_item obj;
obj.set_chto_eto(struct_chto_eto::object);
obj.get_set_object().id = type_item.size();
obj.get_set_object().igrok_mozhet_proyti = false;
obj.get_set_object().blokiruet_zrenie = true;
obj.get_set_object().textura = 'E';
type_item.push_back(obj);

struct_item pochva;
pochva.set_chto_eto(struct_chto_eto::object);
pochva.get_set_object().igrok_mozhet_proyti = true;
pochva.get_set_object().blokiruet_zrenie = false;
pochva.get_set_object().textura = ',';
pochva.get_set_object().id = type_item.size();
pochva.get_set_object().set_pochva(true);
pochva.get_set_object().set_resource(3,true);
pochva.get_set_object().set_id_of_the_item_that_will_be_spawned(2);
type_item.push_back(pochva);
struct_item W;
W.set_chto_eto(struct_chto_eto::object);
W.get_set_object().id = type_item.size();
W.get_set_object().igrok_mozhet_proyti = true;
W.get_set_object().blokiruet_zrenie = false;
W.get_set_object().sytost = 5;
W.get_set_object().textura = 'W';
type_item.push_back(W);
}
void spawn_item(game_state& state, int x, int y, int z, int w, int id){

if(id < 0 || id >= type_item.size()){return;}
long long key = make_key(x,y,z,w);
type_item[id].get_set_xyzw().set_x(x,true);
type_item[id].get_set_xyzw().set_y(y,true);
type_item[id].get_set_xyzw().set_z(z,true);
type_item[id].get_set_xyzw().set_w(w,true);
state.item[key].push_back(type_item[id]);
state.cells_to_index.insert(key);
if(type_item[id].get_set_object().get_pochva() == true){state.pochva_keys.push_back(key);}
}