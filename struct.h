#ifndef STRUCT_H
#define STRUCT_H
#include <vector>
#include <string>
#include <unordered_map>
long long make_key(int x, int y, int z, int w);

enum struct phase_state{
standart,
game_over
};
enum struct struct_chto_eto{
object,
};
struct struct_object{
bool igrok_mozhet_proyti = true;
std::string textura = " ";
int id = -1;
};

struct struct_xyzw{
private:
int x = 0;
int y = 0;
int z = 0;
int w = 0;
public:
int get_x();
int get_y();
int get_z();
int get_w();
void set_x(int chislo, bool ustanovit = 0);
void set_y(int chislo, bool ustanovit = 0);
void set_z(int chislo, bool ustanovit = 0);
void set_w(int chislo, bool ustanovit = 0);
};

struct struct_item{
private:
struct_chto_eto chto_eto;
struct_object object;
struct_xyzw xyzw;
public:
struct_chto_eto get_chto_eto();
void set_chto_eto(struct_chto_eto x);
struct_xyzw& get_set_xyzw();
struct_object& get_set_object();
};

struct game_state{
private:
int igrok_x = 0;
int igrok_y = 0;
int igrok_z = 0;
int igrok_w = 0;
phase_state phase;
struct_xyzw wasd;
int wasd_timer = -1;
public:
std::unordered_map<long long, std::vector<struct_item>> item;
int get_igrok_x();
int get_igrok_y();
int get_igrok_z();
int get_igrok_w();

void set_igrok_x(int x, bool ustanovit = 0);
void set_igrok_y(int x, bool ustanovit = 0);
void set_igrok_z(int x, bool ustanovit = 0);
void set_igrok_w(int x, bool ustanovit = 0);

phase_state get_phase();
void set_phase(phase_state x);
struct_xyzw& get_set_wasd();
int& get_wasd_timer();
void set_wasd_timer(int x);
void update_teleport(game_state& state);
};

bool proverka(game_state& state, const int& x, const int& y, const int& z, const int& w);

#endif