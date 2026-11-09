#include "set_target_id.h"
void set_target_id(game_state& state,struct_item& e){
if(e.get_set_entity().get_what_it_eats() == struct_what_it_eats::herbivorous){
for(int i = 0; i < type_item.size(); ++i){
if(type_item[i].get_chto_eto() == struct_chto_eto::object && type_item[i].get_set_object().sytost > 0){
e.get_set_entity().set_id_tseli(type_item[i].get_set_object().id);
return;
}}
}
else if(e.get_set_entity().get_what_it_eats() == struct_what_it_eats::predator){
for(int i = 0; i < type_item.size(); ++i){
if(type_item[i].get_chto_eto() == struct_chto_eto::entity){
e.get_set_entity().set_id_tseli(type_item[i].get_set_object().id);
return;
}}
}
else if(e.get_set_entity().get_what_it_eats() == struct_what_it_eats::omnivorous){
int id_1 = -1;
int id_2 = -1;

for(int i = 0; i < type_item.size(); ++i){
if(id_1 == -1 && type_item[i].get_chto_eto() == struct_chto_eto::object && type_item[i].get_set_object().sytost > 0){id_1 = i;}
else if(id_2 == -1 && type_item[i].get_chto_eto() == struct_chto_eto::entity){id_2 = i;}
else if(id_1 != -1 && id_2 != -1){break;}
}
if(id_1 == -1 && id_2 == -1){return;}
else if(id_1 != -1 && id_2 == -1){e.get_set_entity().set_id_tseli(id_1);}
else if(id_1 == -1 && id_2 != -1){e.get_set_entity().set_id_tseli(id_2);}
else{

int ex = e.get_set_xyzw().get_x();
int ey = e.get_set_xyzw().get_y();
int ccx = chunk_of(ex);
int ccy = chunk_of(ey);
int id_1_quantity = 0;
int id_2_quantity = 0;
for(int dcx = -1; dcx <= 1; ++dcx){
for(int dcy = -1; dcy <= 1; ++dcy){
long long ckey = make_ckey(ccx + dcx, ccy + dcy);

auto c_it = state.index_by_chunk.find(ckey);
if(c_it == state.index_by_chunk.end()){continue;}

auto id_1_it = c_it->second.find(id_1);
auto id_2_it = c_it->second.find(id_2);
if(id_1_it != c_it->second.end()){id_1_quantity += id_1_it->second.size();}
if(id_2_it != c_it->second.end()){id_2_quantity += id_2_it->second.size();}
}}
if(id_1_quantity >= id_2_quantity){e.get_set_entity().set_id_tseli(id_1);}
else{e.get_set_entity().set_id_tseli(id_2);}
}
}
}