/*
 * Name: Josh Stikeleather
 * Date Submitted: 11/24/2025
 * Lab Section: 003
 * Assignment Name: Lab 10, Breadth-First Search to solve puzzles
 */

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// Reflects what each node represents...
// int with each bit == 0 left of river, bit == 1 right of river
typedef int state;

// Bit position representation for wolf/goat/cabbage/me
bool bit(int x, int i) { return (x>>i) & 1; }
const int wolf=0, goat=1, cabbage=2, me=3;

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from curnode)
void search(state source_node)
{
  queue<state> to_visit;
  to_visit.push(source_node);
  visited[source_node] = true;
  dist[source_node] = 0;
  
  while (!to_visit.empty()) {
    state curnode = to_visit.front();
    to_visit.pop();
    for (state n : nbrs[curnode])
      if (!visited[n]) {
	pred[n] = curnode;
	dist[n] = 1 + dist[curnode];
	visited[n] = true;
	to_visit.push(n);
      }
  }
}

string state_string(state s)
{
  string items[4] = { "wolf", "goat", "cabbage", "you" }, result = "";
  for (int i=0; i<4; i++)
    if (!bit(s, i)) result += items[i] + " ";
  result += " |river| ";
  for (int i=0; i<4; i++)
    if (bit(s, i)) result += items[i] + " ";
  return result;
}

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << state_string(t) << "\n";
  } else {
    cout << "Initial state: " << state_string(s) << "\n";
  }
}

string neighbor_label(int s, int t)
{
  string items[3] = { "wolf", "goat", "cabbage" }, which_cross;
  if (bit(s,me) == bit(t,me)) return "";  // must cross river
  int cross_with = 0;
  for (int i=0; i<3; i++) {
    if (bit(s,i) != bit(t,i) && bit(s,i)==bit(s,me)) { cross_with++; which_cross = items[i]; }
    if (bit(s,i) != bit(t,i) && bit(s,i)!=bit(s,me)) return "";
  }
  if (cross_with > 1) return "";
  if (cross_with == 0) return "Cross alone";
  else return "Cross with " + which_cross;
}

//This helper function is to insure that no "unsafe" items are left on the same side of the river together
//For this to work we need to check both banks of the river
bool isLegal(state currentState, state nextState){
  for(int side = 0; side < 2; side++){ //0 for the left side and 1 for the right
    //These are bool vals to check if whatever item is on the same side of the river as you
    bool youHere = (bit(nextState, me) == side);
    bool wolfHere = (bit(nextState, wolf) == side);
    bool goatHere = (bit(nextState, goat) == side);
    bool cabbageHere = (bit(nextState, cabbage) == side);

    if (!youHere){ //Only check the side of the river you are not on
      if (wolfHere && goatHere){
        return false;
      }
      if (goatHere && cabbageHere){
        return false;
      }
    }
  }
  return true; //If no bad conditions are found return true
}

void build_graph(void)
{
  for (state currentState = 0; currentState < 16; currentState++){ //For loop to run through all 16 possible states

    for (int item = -1; item < 3; item++){ //-1 means you're alone, 0 is wolf, 1 is goat, and 2 is cabbage

      state nextState = currentState; //Start with our current state and modify from there
      nextState = nextState ^ (1 << me); //You always cross the river so flip this bit every time

      if (item != -1){ //If you end up taking an item with you
        //Must check if the item you are trying to bring is on the same side of the river, if not skip
        if (bit(currentState, item) != bit(currentState, me)){
          continue;
        }
        nextState = nextState ^ (1 << item);
      }

      if (isLegal(currentState, nextState)){
        //Now we add this valid move to the graph
        nbrs[currentState].push_back(nextState);
        //Finally we store the label for this edge
        edge_label[make_pair(currentState, nextState)] = neighbor_label(currentState, nextState);
      }
    }
  }
}

int main(void)
{
  build_graph();

  state start = 0, end = 15;
  
  search(start);
  if (visited[end])
    print_path (start, end);
  else
    cout << "No path!\n";
  
  return 0;
}
