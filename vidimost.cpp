#include "vidimost.h"

static void scan(game_state& state,
int cx, int cy, int cz, int cw, double depth,
double start, double end, int radius,
int preobrazovanie_x, int preobrazovanie_y, bool pomenyat_mestami
){
if(depth > radius || start >= end){return;}
for(int lateral = 0; lateral <= depth; ++lateral){
double L = (lateral - 0.5) / (depth + 0.5);
double R = (lateral + 0.5) / (depth - 0.5);
if(R < start){continue;}
if(L > end){break;}
if(depth * depth + lateral * lateral > radius * radius){continue;}

int gx = 0, gy = 0;
if(pomenyat_mestami){
gx = cx + preobrazovanie_x * lateral;
gy = cy + preobrazovanie_y * depth;
}else{
gx = cx + preobrazovanie_x * depth;
gy = cy + preobrazovanie_y * lateral;
}

int gz = cz;
int gw = cw;

long long key = make_key(gx,gy,gz,gw);
state.vidimye_kletki.insert(key);
auto it = state.item.find(key);
bool vidno = true;

if(it != state.item.end()){
for(int index = 0; index < it->second.size(); ++index){
if(it->second[index].get_set_object().blokiruet_zrenie == true){vidno = false; break;}
}
}
if(!vidno){
scan(state, cx, cy, cz, cw, depth + 1.0, start, L,radius,preobrazovanie_x,preobrazovanie_y,pomenyat_mestami);
start = R;
if(start >= end){break;}
}
}
scan(state, cx, cy, cz, cw, depth + 1.0, start, end,radius,preobrazovanie_x,preobrazovanie_y,pomenyat_mestami);
}

void pereschetat_vidimost(game_state& state,struct_item& igrok){
state.vidimye_kletki.clear();
int px = igrok.get_set_xyzw().get_x();
int py = igrok.get_set_xyzw().get_y();
int pz = igrok.get_set_xyzw().get_z();
int pw = igrok.get_set_xyzw().get_w();
long long pkey = make_key(px,py,pz,pw);
state.vidimye_kletki.insert(pkey);

double depth = 1.0;
double start = 0.0;
double end = 1.0;
int radius = 20;
scan(state,px,py,pz,pw,depth,start,end,radius,1,1,false);
scan(state,px,py,pz,pw,depth,start,end,radius,1,1,true);

scan(state,px,py,pz,pw,depth,start,end,radius,-1,1,false);
scan(state,px,py,pz,pw,depth,start,end,radius,-1,1,true);

scan(state,px,py,pz,pw,depth,start,end,radius,-1,-1,false);
scan(state,px,py,pz,pw,depth,start,end,radius,-1,-1,true);

scan(state,px,py,pz,pw,depth,start,end,radius,1,-1,false);
scan(state,px,py,pz,pw,depth,start,end,radius,1,-1,true);

}
