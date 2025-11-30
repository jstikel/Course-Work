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
// First value units of water in A, second units of water in B
typedef pair<int,int> state;

// Each string in edge_label must be one of the following:
const string actions[] = {"Fill A",
                          "Fill B",
                          "Empty A",
                          "Empty B",
                          "Pour A->B",
                          "Pour B->A"};

// GENERIC -- these shouldn't need to be changed...
map<state, bool> visited;         // have we queued up this state for visitation?
map<state, state> pred;           // predecessor state we came from
map<state, int> dist;             // distance (# of hops) from source node
map<state, vector<state>> nbrs;   // vector of neighboring states

map<pair<state,state>, string> edge_label;

// GENERIC (breadth-first search, outward from source_node)
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

// GENERIC
void print_path(state s, state t)
{
  if (s != t) {
    print_path(s, pred[t]);
    cout << edge_label[make_pair(pred[t], t)] << ": " << "[" << t.first << "," << t.second << "]\n";
  } else {
    cout << "Initial state: " << "[" << s.first << "," << s.second << "]\n";
  }
}

void build_graph(void)
{
  const int A = 3; //Max capacity of jug A
  const int B = 4; //Max apacity of jug B
  
  //Now we run through all possible states, where 0 <= a <= A and 0 <= b <= B
  for (int a = 0; a <= A; a++){
    for (int b = 0; b <= B; b++){
      state currentState = make_pair(a, b);
      
      //Now we're going to make a vector of all possible next states
      vector<pair<state, int>> transitions = {
        {make_pair(A, b), 0}, //Fill A
        {make_pair(a, B), 1}, //Fill B
        {make_pair(0, b), 2}, //Empty A
        {make_pair(a, 0), 3}, //Empty B
        {make_pair(a - min(a, B - b), b + min(a, B - b)), 4}, //Pour A into B
        {make_pair(a + min(b, A - a), b - min(b, A - a)), 5}  //Pour B into A
      };
      
      //This adds valid transitions where the next state is different from the current
      for (auto& trans : transitions){
        state next = trans.first;
        int actionIndex = trans.second;
        
        if (next != currentState){
          nbrs[currentState].push_back(next);
          edge_label[make_pair(currentState, next)] = actions[actionIndex];
        }
      }
    }
  }
}

int main(void)
{
  build_graph();

  state start = make_pair(0,0);
  
  for (int i=0; i<5; i++)
    nbrs[make_pair(i,5-i)].push_back(make_pair(-1,-1));
  search (start);
  if (visited[make_pair(-1,-1)]) 
    print_path (start, pred[make_pair(-1,-1)]);
  else
    cout << "No path!\n";
  
  return 0;
}
