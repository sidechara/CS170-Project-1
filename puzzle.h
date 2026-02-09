#include <queue>

using namespace std;

struct State {
    int state[9];
    int blank;
    int depth;
    int heuristic;
};

class Compare {

public:
    bool operator() (State a, State b) {
        if (a.depth + a.heuristic > b.depth + b.heuristic) {
            return true;
        }
        return false;
    }
}; //compare states (arrays) so the min heap can work


class Puzzle {
    State initial;
    //actual current state of puzzle
    priority_queue<State, vector<State>, Compare> pq;
    int solution_depth = 0;
    long nodes_expanded = 0;
    long max_queue = 0;


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