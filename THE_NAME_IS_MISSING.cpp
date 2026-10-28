#include "struct.h"
#include "UI.h"
#include "generation.h"
#include "update_game_loop.h"
#include "item.h"

int main(){
bool restart = false;
do{
restart = false;
clear_console();
game_state state;
struct_item igrok;
igrok.get_set_object().textura = '2';
start_create_type_item();
start();
while(state.get_phase() != phase_state::game_over){

if(state.get_phase() != phase_state::propustit){update(state,igrok);}
else{state.set_phase(phase_state::standart);}
ui(state,igrok);
if(state.get_phase() == phase_state::restart){restart = true; break;}
}
}while(restart);
end();
return 0;
}