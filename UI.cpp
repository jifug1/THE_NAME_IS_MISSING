#include "UI.h"
#include "struct.h"
#include <iostream>
#include <string>
std::string user_string(){
std::string user_input;
std::getline(std::cin, user_input);
return user_input;
}
void D4(game_state& state, long long key, long long key_2){
if(key == key_2){std::cout << "2";}
else if(state.item.count(key) > 0){std::cout << state.item[key][0].get_set_object().textura;}
else{std::cout << ".";}
}
void start(){std::cout << "\n THE_NAME_IS_MISSING\n You terminated this program immediately after launching it.\n Type \'exit\' to terminate this program.\n";
}
void end(){std::cout << "\n return 0;\n";}
void clear_console(){
std::cout << "\033[2J\033[H" << std::flush;
}
void vvod(game_state& state,struct_item& igrok){
bool zanovo = false;
int px = igrok.get_set_xyzw().get_x();
int py = igrok.get_set_xyzw().get_y();
int pz = igrok.get_set_xyzw().get_z();
int pw = igrok.get_set_xyzw().get_w();
do{
zanovo = false;
std::string user_input = user_string();
if(user_input == "8" || user_input == "k"){
    if(proverka(state,px - 1,py,pz,pw))
    igrok.get_set_xyzw().set_x(-1);}
else if(user_input == "2" || user_input == "j"){
    if(proverka(state,px + 1,py,pz,pw))
    igrok.get_set_xyzw().set_x(1);}
else if(user_input == "4" || user_input == "h"){
    if(proverka(state,px,py - 1,pz,pw))
    igrok.get_set_xyzw().set_y(-1);}
else if(user_input == "6" || user_input == "l"){
    if(proverka(state,px,py + 1,pz,pw))
    igrok.get_set_xyzw().set_y(1);}
else if(user_input == "44" || user_input == "hh"){
    if(proverka(state,px,py,pz+1,pw))
    igrok.get_set_xyzw().set_z(1);}
else if(user_input == "66" || user_input == "ll"){
    if(proverka(state,px,py,pz-1,pw))
    igrok.get_set_xyzw().set_z(-1);}
else if(user_input == "88" || user_input == "kk"){
    if(proverka(state,px,py,pz,pw+1))
    igrok.get_set_xyzw().set_w(1);}
else if(user_input == "22" || user_input == "jj"){
    if(proverka(state,px,py,pz,pw-1))
    igrok.get_set_xyzw().set_w(-1);}
else if(user_input == "9" || user_input == "u"){
    if((proverka(state,px-1,py,pz,pw) || proverka(state,px,py+1,pz,pw)) && proverka(state,px-1,py+1,pz,pw)){
    igrok.get_set_xyzw().set_x(-1); 
    igrok.get_set_xyzw().set_y(1);}}
else if(user_input == "7" || user_input == "y"){
    if((proverka(state,px-1,py,pz,pw) || proverka(state,px,py-1,pz,pw)) && proverka(state,px-1,py-1,pz,pw)){
    igrok.get_set_xyzw().set_x(-1); 
    igrok.get_set_xyzw().set_y(-1);}}
else if(user_input == "3" || user_input == "n"){
    if((proverka(state,px+1,py,pz,pw) || proverka(state,px,py+1,pz,pw)) && proverka(state,px+1,py+1,pz,pw)){
    igrok.get_set_xyzw().set_x(1); 
    igrok.get_set_xyzw().set_y(1);}}
else if(user_input == "1" || user_input == "b"){
    if((proverka(state,px+1,py,pz,pw) || proverka(state,px,py-1,pz,pw)) && proverka(state,px+1,py-1,pz,pw)){
    igrok.get_set_xyzw().set_x(1); 
    igrok.get_set_xyzw().set_y(-1);}}
else if(user_input == "5" || user_input == "."){return;}
else if(user_input == "exit"){state.set_phase(phase_state::game_over); return;}
else{
std::cout << " Unknown command: \'" << user_input << "\'"; 
zanovo = true;
}
}while(zanovo);
}
void ne_povtoryaisya(game_state& state, int& x_maloe, int& x_bolshoe,
int& y_maloe, int& y_bolshoe, struct_item& igrok
){
    const int VIEW_W = 20;
    const int VIEW_H = 40;   

    int px = igrok.get_set_xyzw().get_x();
    int py = igrok.get_set_xyzw().get_y();

    int cell_x = px / VIEW_W;
    if (px < 0 && px % VIEW_W != 0) {--cell_x;}

    int cell_y = py / VIEW_H;
    if (py < 0 && py % VIEW_H != 0) {--cell_y;}

    x_maloe = cell_x * VIEW_W;
    x_bolshoe = x_maloe + VIEW_W;
    y_maloe = cell_y * VIEW_H;
    y_bolshoe = y_maloe + VIEW_H;
}

void ui(game_state& state, struct_item& igrok){
if(state.get_phase() == phase_state::game_over){return;}
        int x_maloe = -100;
        int x_bolshoe = -80;
        int y_maloe = -100;
        int y_bolshoe = -60;
        ne_povtoryaisya(state,x_maloe,x_bolshoe,y_maloe,y_bolshoe,igrok);
int w = MAX_W;
long long key_2 = make_key(igrok.get_set_xyzw().get_x(), igrok.get_set_xyzw().get_y(), igrok.get_set_xyzw().get_z(), igrok.get_set_xyzw().get_w());
if(state.nachalo == false){clear_console();}
else{state.nachalo = false;}
for(int x = x_maloe; x < x_bolshoe; ++x){
for(int y = y_maloe; y < y_bolshoe; ++y){

if(igrok.get_set_xyzw().get_x() == x && igrok.get_set_xyzw().get_y() == y){std::cout << "2";}
else{
long long key = make_key(x,y,igrok.get_set_xyzw().get_z(), igrok.get_set_xyzw().get_w());

if(state.vidimye_kletki.count(key) > 0){
if(state.item.count(key) > 0){
std::cout << state.item[key][0].get_set_object().textura;
}
else{std::cout << ".";}
}
else{std::cout << " ";}
}}
   if(x >= x_bolshoe - (MAX_W - MIN_W + 1)){
    if(w >= MIN_W){
    std::cout << " ";
    for(int z = MAX_Z; z >= MIN_Z; --z){
    long long key = make_key(igrok.get_set_xyzw().get_x(),igrok.get_set_xyzw().get_y(),z,w);
    D4(state,key,key_2);
    }
    --w;
    }
   }
std::cout << "\n";
}
vvod(state,igrok);
}
