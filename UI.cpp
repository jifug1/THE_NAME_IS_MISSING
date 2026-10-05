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
void start(){std::cout << "\n THE_NAME_IS_MISSING\n You terminated this program immediately after launching it.\n Type \'exit\' to terminate this program.\n";}
void end(){std::cout << "\n return 0;\n";}
void vvod(game_state& state){
std::string user_input = user_string();
if(user_input == "8"){state.set_igrok_x(-1);}
else if(user_input == "2"){state.set_igrok_x(1);}
else if(user_input == "4"){state.set_igrok_y(-1);}
else if(user_input == "6"){state.set_igrok_y(1);}
else if(user_input == "44"){state.set_igrok_z(1);}
else if(user_input == "66"){state.set_igrok_z(-1);}
else if(user_input == "88"){state.set_igrok_w(1);}
else if(user_input == "22"){state.set_igrok_w(-1);}
    else if(user_input == "86"){state.set_igrok_x(-1); state.set_igrok_y(1);}
    else if(user_input == "68"){state.set_igrok_y(1); state.set_igrok_x(-1);}
    else if(user_input == "84"){state.set_igrok_x(-1); state.set_igrok_y(-1);}
    else if(user_input == "48"){state.set_igrok_y(-1); state.set_igrok_x(-1);}
    else if(user_input == "26"){state.set_igrok_x(1); state.set_igrok_y(1);}
    else if(user_input == "62"){state.set_igrok_y(1); state.set_igrok_x(1);}
    else if(user_input == "24"){state.set_igrok_x(1); state.set_igrok_y(-1);}
    else if(user_input == "42"){state.set_igrok_y(-1); state.set_igrok_x(1);}
else if(user_input == "exit"){state.set_phase(phase_state::game_over); return;}
else{return;}
}
void ne_povtoryaisya(game_state& state, int& x_maloe, int& x_bolshoe,
int& y_maloe, int& y_bolshoe
){
    const int VIEW_W = 20;
    const int VIEW_H = 40;   

    int px = state.get_igrok_x();
    int py = state.get_igrok_y();

    int cell_x = px / VIEW_W;
    if (px < 0 && px % VIEW_W != 0) {--cell_x;}

    int cell_y = py / VIEW_H;
    if (py < 0 && py % VIEW_H != 0) {--cell_y;}

    x_maloe = cell_x * VIEW_W;
    x_bolshoe = x_maloe + VIEW_W;
    y_maloe = cell_y * VIEW_H;
    y_bolshoe = y_maloe + VIEW_H;
}

void ui(game_state& state){
if(state.get_phase() == phase_state::game_over){return;}
        int x_maloe = -100;
        int x_bolshoe = -80;
        int y_maloe = -100;
        int y_bolshoe = -60;
        ne_povtoryaisya(state,x_maloe,x_bolshoe,y_maloe,y_bolshoe);
int w = MAX_W;
long long key_2 = make_key(state.get_igrok_x(), state.get_igrok_y(), state.get_igrok_z(), state.get_igrok_w());
for(int x = x_maloe; x < x_bolshoe; ++x){
for(int y = y_maloe; y < y_bolshoe; ++y){

if(state.get_igrok_x() == x && state.get_igrok_y() == y){std::cout << "2";}
else{
long long key = make_key(x,y,state.get_igrok_z(), state.get_igrok_w());

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
    long long key = make_key(state.get_igrok_x(),state.get_igrok_y(),z,w);
    D4(state,key,key_2);
    }
    --w;
    }
   }
std::cout << "\n";
}
vvod(state);
}
