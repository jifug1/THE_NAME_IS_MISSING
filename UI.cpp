#include "UI.h"
#include "struct.h"
#include <iostream>
#include <string>
#include <limits>
void ignore(){
std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
void get(){
std::cout << " std::cin.get() ";
std::cin.get();
}
char set_igrok_textura(){
char textura = '2';
std::cout << " char: ";
std::cin >> std::noskipws >> textura;
std::cin >> std::skipws;
if(std::cin.fail() || textura == '\n'){std::cin.clear(); ignore(); return '2';}
ignore();
return textura;
}
std::string user_string(){
std::string user_input;
std::getline(std::cin, user_input);
return user_input;
}
int user_int(){
int user_input = 0;
std::cin >> user_input;
if(std::cin.fail()){std::cin.clear(); ignore(); return 0;}
return user_input;
}
char user_char(){
char user_input = ' ';
std::cin >> user_input;
if(std::cin.fail()){std::cin.clear(); ignore(); return ' ';}
return user_input;
}
void print_pt(struct_item& igrok){
std::cout << igrok.get_set_object().textura;
}
void print_kt(game_state& state, long long key){
auto it = state.item.find(key);
if(it == state.item.end() || it->second.empty()){return;}
uint8_t current_index = 0;
if(state.v < it->second.size()){
current_index = state.v;
}
std::cout << it->second[current_index].get_set_object().textura;
}
void D4(game_state& state, struct_item& igrok, long long key, long long key_2){
if(key == key_2){print_pt(igrok);}
else if(state.item.count(key) > 0){print_kt(state,key);}
else{std::cout << VOID;}
}
void start(){std::cout << "\n THE_NAME_IS_MISSING\n You terminated this program immediately after launching it.\n Type \'exit\' to terminate this program.\n";
}
void end(){std::cout << "\n return 0;\n";}
void clear_console(){
std::cout << "\033[2J\033[H" << std::flush;
}
void get_pochva_keys(game_state& state){
for(int i = 0; i < state.pochva_keys.size(); ++i){
auto it = state.item.find(state.pochva_keys[i]);
auto& vec = it->second;
if(it == state.item.end()){continue;}
for(int j = 0; j < vec.size(); ++j){
if(vec[j].get_set_object().get_pochva() == false){continue;}
std::cout << " " << state.pochva_keys[i] << " " << vec[j].get_set_object().get_resource() << '\n';
}}}
void skip(game_state& state){state.set_phase(phase_state::propustit);}
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
else if(user_input == "|"){
std::cout << " int: ";
int podozhdat = user_int();
if(podozhdat > 0){state.set_propustit_vvod_timer(podozhdat); ignore();}
else{skip(state);}
}
else if(user_input == "state.timer_pochva"){std::cout << " " << state.timer_pochva << " ";
skip(state);
get();
}
else if(user_input == "restart"){state.set_phase(phase_state::restart); return;}
else if(user_input == "get_pochva_keys(state)"){get_pochva_keys(state); skip(state); get();}
else if(user_input == "state.pochva_keys.size()"){std::cout << " " << state.pochva_keys.size() << " "; get();}
else if(user_input == "v"){
std::cout << " uint8_t v == \'" << static_cast<int>(state.v) << "\' v = ";
state.v = user_int();
std::cout << " v == \'" << static_cast<int>(state.v) << "\' ";
skip(state);
ignore();
get();
ignore();
}
else if(user_input == "set_igrok_textura()"){igrok.get_set_object().textura = set_igrok_textura();}
else if(user_input == "VOID"){
std::cout << " char VOID == \'" << VOID << "\' VOID = ";
VOID = user_char();
std::cout << " VOID == \'" << VOID << "\' ";
skip(state);
ignore();
get();
ignore();
}
else if(user_input == "THE_UNKNOWN"){
std::cout << " char THE_UNKNOWN == \'" << THE_UNKNOWN << "\' THE_UNKNOWN = ";
THE_UNKNOWN = user_char();
std::cout << " THE_UNKNOWN == \'" << THE_UNKNOWN << "\' ";
skip(state);
ignore();
get();
ignore();
}
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

if(igrok.get_set_xyzw().get_x() == x && igrok.get_set_xyzw().get_y() == y){print_pt(igrok);}
else{
long long key = make_key(x,y,igrok.get_set_xyzw().get_z(), igrok.get_set_xyzw().get_w());

if(state.vidimye_kletki.count(key) > 0){
if(state.item.count(key) > 0){
print_kt(state,key);
}
else{std::cout << VOID;}
}
else{std::cout << THE_UNKNOWN;}
}}
   if(x >= x_bolshoe - (MAX_W - MIN_W + 1)){
    if(w >= MIN_W){
    std::cout << " ";
    for(int z = MAX_Z; z >= MIN_Z; --z){
    long long key = make_key(igrok.get_set_xyzw().get_x(),igrok.get_set_xyzw().get_y(),z,w);
    D4(state,igrok,key,key_2);
    }
    --w;
    }
   }
std::cout << "\n";
}
if(state.get_propustit_vvod_timer() <= 0){vvod(state,igrok);}
else{state.update_propustit_vvod();}
}