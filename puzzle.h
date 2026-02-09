#include <queue>

using namespace std;

//Stores potential state of a puzzle at any point during solving
struct State {
    int state[9]; //encodes which tile is in each of the 9 indexed slots
    int blank; //index of blank tile
    int depth; //depth of state relative to initial
    int heuristic; //heuristic value of state
};

//Allows us to compare two States
class Compare {

public:
    bool operator() (State a, State b) { //Returns whether two States are in correct order (needs reordering)
        if (a.depth + a.heuristic > b.depth + b.heuristic) {
            return true;
        }
        return false;
    }
};


class Puzzle {
    State initial;
    priority_queue<State, vector<State>, Compare> pq; //stores States in order of estimated cost to goal
    long nodes_expanded = 0; //total nodes expanded during solving
    long max_queue = 0; //max number of nodes in the queue during solving


public:

    Puzzle(int*);

    State solve(int);
    bool goal(State);
    void expand(State, int);
    int misplaced_tile(State);
    int manhattan_distance(State);

    State getInitial() { return initial; }

    long getMaxExpanded() { return nodes_expanded; }

    long getMaxQueue() { return max_queue; }



};