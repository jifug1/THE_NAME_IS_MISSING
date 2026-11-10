#include "struct.h"
#include "UI.h"
#include "update_game_loop.h"
#include "item.h"
#include "vidimost.h"

int main(){
bool restart = false;
do{
restart = false;
clear_console();
game_state state;
struct_item igrok;
igrok.get_set_object().textura = '2';
igrok.get_set_entity().set_sytost(30,true);
std::uniform_int_distribution<int> local(5,15);
igrok.get_set_entity().set_damage(local(chislo),true);
std::uniform_int_distribution<int> local_2(80,120);
igrok.get_set_entity().set_health(local_2(chislo),true);
start_create_type_item();
start();
while(state.get_phase() != phase_state::game_over){

if(state.get_phase() != phase_state::propustit){update(state,igrok);}
else{state.set_phase(phase_state::standart);}
pereschetat_vidimost(state,igrok);
ui(state,igrok);
if(state.get_phase() == phase_state::restart){restart = true; break;}
}
}while(restart);
end();
return 0;
}