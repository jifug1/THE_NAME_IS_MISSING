#ifndef STRUCT_H
#define STRUCT_H
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
struct game_state;
extern const int chunk_size;
extern const int nuzhno_travy_v_chunke;
extern const int X_v_chunke;
extern const int iterations;
extern const int INF;
long long make_key(int x, int y, int z, int w);
long long make_ckey(int x,int y);
int chunk_of(int position);

enum struct phase_state{
standart,
game_over,
propustit
};
enum struct struct_chto_eto{
object,
entity,
};
struct struct_object{
bool igrok_mozhet_proyti = true;
char textura = ' ';
int id = -1;
int sytost = 0;
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

struct struct_puti{
int g = 1000000;
int h = 0;
int f = 0;
struct_xyzw xyzw;
struct_xyzw otkuda_prishli;
};
struct struct_entity{
private:
struct_xyzw mesto_tseli;
std::vector<struct_xyzw> marshrut;
int id_tseli = -1;
int sytost = 20;
int kak_chasto_spat = 40;
int son = kak_chasto_spat;
bool spit = false;
bool mertv = false;
int counter = 0;
long long target_key = -1;
int target_index = -1;
public:
struct_xyzw& get_set_mesto_tseli();
std::vector<struct_xyzw>& get_set_marshrut();
int get_id_tseli();
void set_id_tseli(int x);
int get_sytost();
void set_sytost(int x, bool ustanovit = false);
int get_son();
void set_son(int x, bool ustanovit = false);
void update_sytost_son();
int get_kak_chasto_spat();
void set_kak_chasto_spat(int x);
int get_spit();
void set_spit(bool x);
bool get_mertv();
int get_counter();
void set_counter(int x,bool ustanovit = 0);
long long get_target_key();
void set_target_key(long long x);
int get_target_index();
void set_target_index(int x);
};
struct struct_item{
private:
struct_chto_eto chto_eto;
struct_object object;
struct_xyzw xyzw;
struct_entity entity;
public:
struct_chto_eto get_chto_eto();
void set_chto_eto(struct_chto_eto x);
struct_xyzw& get_set_xyzw();
struct_object& get_set_object();
struct_entity& get_set_entity();
};

struct game_state{
private:
int igrok_x = 0;
int igrok_y = 0;
int igrok_z = 0;
int igrok_w = 0;
phase_state phase = phase_state::standart;
struct_xyzw wasd;
int wasd_timer = -1;
public:
std::unordered_map<long long, std::vector<struct_item>> item;
std::vector<long long> entity_keys;
std::unordered_set<long long> loaded_chunks;
//std::unordered_map<int, std::unordered_set<long long>> index_by_id;
std::unordered_map<long long, std::unordered_set<long long>> index_by_chunk;
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
int get_wasd_timer() const;
void set_wasd_timer(int x);
void update_teleport();
};

bool proverka(game_state& state, const int x, const int y, const int z, const int w);

#endif