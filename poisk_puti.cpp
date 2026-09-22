#include "poisk_puti.h"
#include <cstdlib>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

int heuristic(struct_xyzw& a, struct_xyzw& b){
return (std::abs(a.get_x() - b.get_x())) +
(std::abs(a.get_y() - b.get_y())) +
(std::abs(a.get_z() - b.get_z())) +
(std::abs(a.get_w() - b.get_w()));
}

static const int dx[8] = { 1, -1, 0,  0, 0,  0, 0,  0};
static const int dy[8] = { 0,  0, 1, -1, 0,  0, 0,  0};
static const int dz[8] = { 0,  0, 0,  0, 1, -1, 0,  0};
static const int dw[8] = { 0,  0, 0,  0, 0,  0, 1, -1};

struct Node{
    int f;
    long long key;
    bool operator<(const Node& other) const {
    return f > other.f;
    }
};

std::vector<struct_xyzw> nayti_put(game_state& state, struct_item& e, struct_xyzw& A, struct_xyzw& B){
std::vector<struct_xyzw> path;
if (A.get_x() == B.get_x() && A.get_y() == B.get_y() &&
    A.get_z() == B.get_z() && A.get_w() == B.get_w()){
    path.push_back(A);
    return path;
}
long long key_A = make_key(A.get_x(), A.get_y(), A.get_z(), A.get_w());
long long key_B = make_key(B.get_x(), B.get_y(), B.get_z(), B.get_w());

std::unordered_map<long long, struct_puti> nodes;  
std::unordered_set<long long> closed;             
std::priority_queue<Node> open;

struct_puti start;
start.g = 0;
start.h = heuristic(A, B);
start.f = start.g + start.h;
start.xyzw = A;
start.otkuda_prishli = A;
nodes[key_A] = start;
open.push({start.f, key_A});

bool found = false;

int ogranichenie = iterations;
while (!open.empty() && ogranichenie > 0){
Node top = open.top();
open.pop();
long long cur_key = top.key;
if (closed.count(cur_key)) {continue;}
if (cur_key == key_B){found = true; break;}

closed.insert(cur_key);

struct_puti cur = nodes[cur_key];
int cx = cur.xyzw.get_x();
int cy = cur.xyzw.get_y();
int cz = cur.xyzw.get_z();
int cw = cur.xyzw.get_w();

for (int i = 0; i < 8; ++i){
int nx = cx + dx[i];
int ny = cy + dy[i];
int nz = cz + dz[i];
int nw = cw + dw[i];

if (nz < -1 || nz > 1) {continue;}
if (nw < -1 || nw > 1) {continue;}

long long nkey = make_key(nx, ny, nz, nw);

if (closed.count(nkey)) {continue;}
if (!proverka(state, nx, ny, nz, nw)) {continue;}

int new_g = cur.g + 1;

auto it = nodes.find(nkey);
if (it == nodes.end()){

struct_puti n;
n.g = new_g;
n.h = std::abs(nx - B.get_x()) + std::abs(ny - B.get_y())
+ std::abs(nz - B.get_z()) + std::abs(nw - B.get_w());
n.f = n.g + n.h;
n.xyzw.set_x(nx, true);
n.xyzw.set_y(ny, true);
n.xyzw.set_z(nz, true);
n.xyzw.set_w(nw, true);
n.otkuda_prishli = cur.xyzw;
nodes[nkey] = n;
open.push({n.f, nkey});
}
else if (new_g < it->second.g){

it->second.g = new_g;
it->second.f = it->second.g + it->second.h;
it->second.otkuda_prishli = cur.xyzw;
open.push({it->second.f, nkey});
}
}
--ogranichenie;
}
if(ogranichenie <= 0){e.get_set_entity().set_counter(5);}
if (!found) {return path;} 
    
std::vector<struct_xyzw> reversed;
long long k = key_B;
while (k != key_A){
reversed.push_back(nodes[k].xyzw);
struct_xyzw parent = nodes[k].otkuda_prishli;
long long pkey = make_key(parent.get_x(), parent.get_y(),
parent.get_z(), parent.get_w());
if (pkey == k) {break;}
k = pkey;
}
reversed.push_back(A);

path.reserve(reversed.size());
for (int i = (int)reversed.size() - 1; i >= 0; --i){
path.push_back(reversed[i]);
}
return path;
}