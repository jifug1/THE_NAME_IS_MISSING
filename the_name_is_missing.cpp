#include "struct.h"
#include "UI.h"
#include "generation.h"
#include "update_game_loop.h"

int main(){
game_state state;
start();
while(state.get_phase() != phase_state::game_over){

update(state);
ui(state);
}
return 0;
}