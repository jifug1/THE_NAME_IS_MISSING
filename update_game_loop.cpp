#include "update_game_loop.h"
#include "generation.h"
#include "poisk_puti.h"
#include "update_index_by_id.h"
#include <algorithm>

struct move_task{
long long old_key;
int old_index;
int new_x, new_y, new_z ,new_w;
};
struct eat_task{
long long key;
int x,y,z,w;
int id = -1;
};

void update_eat(game_state& state, long long key, int x, int y, int z, int w, int id){
auto it = state.item.find(key);
if(it == state.item.end()){return;}
auto& vec = it->second;


for(int index = vec.size() - 1; index >= 0; --index){
if(vec[index].get_set_object().id == id &&
vec[index].get_set_xyzw().get_x() == x &&
vec[index].get_set_xyzw().get_y() == y &&
vec[index].get_set_xyzw().get_z() == z &&
vec[index].get_set_xyzw().get_w() == w
){
vec.erase(vec.begin()+index);
update_index_for_cell(state,key,x,y,id);
break;
}
}
if(vec.empty()){
state.item.erase(it);
}
}

void peremestit_entity(game_state& state,
long long old_key, int old_index,
int new_x, int new_y, int new_z, int new_w){
int id = state.item[old_key][old_index].get_set_object().id;
 
int old_x = state.item[old_key][old_index].get_set_xyzw().get_x();
int old_y = state.item[old_key][old_index].get_set_xyzw().get_y();

struct_item entity_copy = std::move(state.item[old_key][old_index]);
state.item[old_key].erase(state.item[old_key].begin() + old_index);
update_index_for_cell(state,old_key,old_x,old_y,id);

if (state.item[old_key].empty()){
state.item.erase(old_key);
}

bool eshe_est_na_starom = false;
if (state.item.count(old_key) > 0){
for (int i = 0; i < state.item[old_key].size(); ++i){
if (state.item[old_key][i].get_chto_eto() == struct_chto_eto::entity){
eshe_est_na_starom = true;
break;
}}}
if (!eshe_est_na_starom){
for (int i = 0; i < state.entity_keys.size(); ++i){
if (state.entity_keys[i] == old_key){
state.entity_keys.erase(state.entity_keys.begin() + i);
break;
}}}

entity_copy.get_set_xyzw().set_x(new_x, true);
entity_copy.get_set_xyzw().set_y(new_y, true);
entity_copy.get_set_xyzw().set_z(new_z, true);
entity_copy.get_set_xyzw().set_w(new_w, true);

long long new_key = make_key(new_x, new_y, new_z, new_w);

bool uzhe_byl = false;
for (int i = 0; i < state.entity_keys.size(); ++i){
if (state.entity_keys[i] == new_key){
uzhe_byl = true;
break;
}}

state.item[new_key].push_back(entity_copy);

if (!uzhe_byl){
state.entity_keys.push_back(new_key);
}
index_cell(state, new_key);
}

void chunk_proverka(game_state& state){
int px = state.get_igrok_x();
int py = state.get_igrok_y();
int cx0 = chunk_of(px - (chunk_size * 2));
int cx1 = chunk_of(px + (chunk_size * 2));
int cy0 = chunk_of(py - (chunk_size * 2));
int cy1 = chunk_of(py + (chunk_size * 2));
for(int cx = cx0; cx <= cx1; ++cx){
for(int cy = cy0; cy <= cy1; ++cy){
generate_chunk(state,cx * chunk_size,cy * chunk_size);
}}}


void move_entity(game_state& state, std::vector<move_task>& moves, std::vector<eat_task>& delete_eat, struct_item& e,std::vector<struct_xyzw>& tsel, long long key, int i){

if(!tsel.empty() && tsel[0].get_x() == e.get_set_xyzw().get_x() &&
tsel[0].get_y() == e.get_set_xyzw().get_y() &&
tsel[0].get_z() == e.get_set_xyzw().get_z() &&
tsel[0].get_w() == e.get_set_xyzw().get_w()
){tsel.erase(tsel.begin()+0);}
if(tsel.empty()){
for(int index = state.item[key].size() - 1; index >= 0; --index){
if(i == index){continue;}
if(state.item[key][index].get_set_object().id == e.get_set_entity().get_id_tseli()){
    e.get_set_entity().set_sytost(state.item[key][index].get_set_object().sytost,false);
    delete_eat.push_back({key,
        state.item[key][index].get_set_xyzw().get_x(),
        state.item[key][index].get_set_xyzw().get_y(),
        state.item[key][index].get_set_xyzw().get_z(),
        state.item[key][index].get_set_xyzw().get_w(),
        state.item[key][index].get_set_object().id});
}
}
return;}

auto& target = tsel[0];

    if(target.get_x() < e.get_set_xyzw().get_x()){e.get_set_xyzw().set_x(-1);}
    else if(target.get_x() > e.get_set_xyzw().get_x()){e.get_set_xyzw().set_x(1);}
    else if(target.get_y() < e.get_set_xyzw().get_y()){e.get_set_xyzw().set_y(-1);}
    else if(target.get_y() > e.get_set_xyzw().get_y()){e.get_set_xyzw().set_y(1);}
    else if(target.get_z() < e.get_set_xyzw().get_z()){e.get_set_xyzw().set_z(-1);}
    else if(target.get_z() > e.get_set_xyzw().get_z()){e.get_set_xyzw().set_z(1);}
    else if(target.get_w() < e.get_set_xyzw().get_w()){e.get_set_xyzw().set_w(-1);}
    else if(target.get_w() > e.get_set_xyzw().get_w()){e.get_set_xyzw().set_w(1);}
    
    if(target.get_x() == e.get_set_xyzw().get_x() &&
    target.get_y() == e.get_set_xyzw().get_y() &&
    target.get_z() == e.get_set_xyzw().get_z() &&
    target.get_w() == e.get_set_xyzw().get_w()
    ){
    tsel.erase(tsel.begin()+0);
    }
    moves.push_back({key,i,e.get_set_xyzw().get_x(),e.get_set_xyzw().get_y(),e.get_set_xyzw().get_z(),e.get_set_xyzw().get_w()});
}


void nayti_tsel_po_id(game_state& state,struct_item& e, long long& key_2, int& i_2){
    key_2 = -1;
    i_2 = -1;

    int ex = e.get_set_xyzw().get_x();
    int ey = e.get_set_xyzw().get_y();
    int target_id = e.get_set_entity().get_id_tseli();

    int best_dist = INF;
    int ccx = chunk_of(ex);
    int ccy = chunk_of(ey);

    for(int dcx = -1; dcx <= 1; ++dcx){
    for(int dcy = -1; dcy <= 1; ++dcy){
        long long ckey = make_ckey(ccx + dcx, ccy + dcy);

        auto c_it = state.index_by_chunk.find(ckey);
        if(c_it == state.index_by_chunk.end()) { continue; }

        auto id_it = c_it->second.find(target_id);
        if(id_it == c_it->second.end()) { continue; }

        for(long long k : id_it->second){
            auto it = state.item.find(k);
            if(it == state.item.end()) { continue; }
            for(int i = 0; i < (int)it->second.size(); ++i){
                if(it->second[i].get_set_object().id != target_id) { continue; }
                int d = heuristic(e.get_set_xyzw(), it->second[i].get_set_xyzw());
                if(d < best_dist){ best_dist = d; key_2 = k; i_2 = i; }
            }
        }
    }}
}



    void update_entity(game_state& state){
std::vector<move_task> moves;
std::vector<eat_task> delete_eat;
for(int index = state.entity_keys.size() - 1; index >= 0; --index){
long long key = state.entity_keys[index];
auto it = state.item.find(key);
if(it == state.item.end()){state.entity_keys.erase(state.entity_keys.begin()+index);continue;}

auto& vec = it->second;

for(int i = vec.size() - 1; i >= 0; --i){
struct_item& e = vec[i];
if(e.get_chto_eto() == struct_chto_eto::entity){
e.get_set_entity().update_sytost_bodrost();
e.update_sytost_obj_sytost();
if(e.get_set_entity().get_spit() == true){continue;}

if(e.get_set_entity().get_mertv() == true){
    int ex_ = e.get_set_xyzw().get_x();
    int ey_ = e.get_set_xyzw().get_y();
    int id = e.get_set_object().id;
    vec.erase(it->second.begin()+i);
update_index_for_cell(state,key,ex_,ey_,id);
if(vec.empty()){
    state.item.erase(key); 
    state.entity_keys.erase(state.entity_keys.begin()+index); 
    break;
}
    continue;
}


if(e.get_set_entity().get_id_tseli() < 0){continue;}
if(e.get_set_entity().get_counter() > 0){e.get_set_entity().set_counter(-1,false); continue;}
    long long key_2 = e.get_set_entity().get_target_key();
    int i_2 = e.get_set_entity().get_target_index();
    bool target_valid = false;
    if(key_2 > -1){
    auto t_it = state.item.find(key_2);
    if(t_it != state.item.end() && i_2 >= 0 && i_2 < (int)t_it->second.size()){
    if(t_it->second[i_2].get_set_object().id == e.get_set_entity().get_id_tseli() 
    ){
    target_valid = true;
    }
    }
    }

    if(!target_valid){
    key_2 = -1;
    i_2 = -1;
    nayti_tsel_po_id(state,e,key_2,i_2);
    e.get_set_entity().set_target_key(key_2);
    e.get_set_entity().set_target_index(i_2);
    }

    if(key_2 == -1){continue;}
    
    std::vector<struct_xyzw>& tsel = e.get_set_entity().get_set_marshrut();
    if(tsel.empty()){tsel = nayti_put(state,e,e.get_set_xyzw(),state.item[key_2][i_2].get_set_xyzw());}
    move_entity(state,moves,delete_eat,e,tsel,key,i);
}}
}
std::sort(moves.begin(),moves.end(), [](const move_task& a, const move_task& b){
if(a.old_key == b.old_key){return a.old_index > b.old_index;}
return a.old_key < b.old_key;
});
for(auto& m : moves){
auto it = state.item.find(m.old_key);
if(it == state.item.end()){continue;}
if(m.old_index < 0 || m.old_index >= (int)it->second.size()){continue;}
if(it->second[m.old_index].get_chto_eto() != struct_chto_eto::entity){continue;}
peremestit_entity(state,m.old_key,m.old_index,m.new_x,m.new_y,m.new_z,m.new_w);}
for(auto& e : delete_eat){
update_eat(state, e.key,e.x,e.y,e.z,e.w,e.id);
}
}

void update(game_state& state){
chunk_proverka(state);
update_entity(state);
state.update_W_Q();
state.update_teleport();
}