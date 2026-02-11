#include "puzzle.h"

#include <cmath>
#include <iostream>

Puzzle::Puzzle(int* array) {
    for (int i = 0; i < 9; i++) {
        initial.state[i] = array[i];
        if (array[i] == 0) {
            initial.blank = i; //Initialize index of blank tile
        }
    }
    initial.depth = 0;


}

bool Puzzle::goal(State s) {
    for (int i = 0; i < 8; i++) {
        if (s.state[i]-1 != i) { //Checks if tile found in a spot is equal to the index
            return false;
        }
    }
    return true;
}

void Puzzle::expand(State s, int algorithm) {
    int row = s.blank/3;
    int col = s.blank%3;
    if (row > 0) { //If blank tile can move up
        State up;
        for (int i = 0; i < 9; i++) {
            if (i/3 == row-1 && i%3 == col) {
                up.state[i] = 0; //Move blank tile to new place
                up.state[i+3] = s.state[i]; //Swap the physical tile
                up.blank = i;
            } else if (s.state[i] != 0) {
                up.state[i] = s.state[i];
            }
        }
        up.depth = s.depth+1;
        if (algorithm == 1) {
            up.heuristic = misplaced_tile(up);
        } else if (algorithm == 2) {
            up.heuristic = manhattan_distance(up);
        } else {
            up.heuristic = 0;
        }
        pq.push(up);

    }
    if (col > 0) { //If blank tile can move left
        State left;
        for (int i = 0; i < 9; i++) {
            if (i/3 == row && i%3 == col-1) {
                left.state[i] = 0; //Move blank tile to new place
                left.state[i+1] = s.state[i]; //Swap the physical tile
                left.blank = i;
            } else if (s.state[i] != 0) {
                left.state[i] = s.state[i];
            }
        }
        left.depth = s.depth+1;
        if (algorithm == 1) {
            left.heuristic = misplaced_tile(left);
        } else if (algorithm == 2) {
            left.heuristic = manhattan_distance(left);
        } else {
            left.heuristic = 0;
        }
        pq.push(left);

    }
    if (col < 2) { //If blank tile can move right
        State right;
        for (int i = 0; i < 9; i++) {
            if (i/3 == row && i%3 == col+1) {
                right.state[i] = 0; //Move blank tile to new place
                right.state[i-1] = s.state[i]; //Swap the physical tile
                right.blank = i;
            } else if (s.state[i] != 0) {
                right.state[i] = s.state[i];
            }
        }
        right.depth = s.depth+1;
        if (algorithm == 1) {
            right.heuristic = misplaced_tile(right);
        } else if (algorithm == 2) {
            right.heuristic = manhattan_distance(right);
        } else {
            right.heuristic = 0;
        }
        pq.push(right);

    }
    if (row < 2) { //If blank tile can move down
        State down;
        for (int i = 0; i < 9; i++) {
            if (i/3 == row+1 && i%3 == col) {
                down.state[i] = 0; //Move blank tile to new place
                down.state[i-3] = s.state[i]; //Swap the physical tile
                down.blank = i;
            } else if (s.state[i] != 0) {
                down.state[i] = s.state[i];
            }
        }
        down.depth = s.depth+1;
        if (algorithm == 1) {
            down.heuristic = misplaced_tile(down);
        } else if (algorithm == 2) {
            down.heuristic = manhattan_distance(down);
        } else {
            down.heuristic = 0;
        }
        pq.push(down);

    }
}

int Puzzle::misplaced_tile(State s) { //Heuristic based on number of tiles (not including blank) that are misplaced
    int misplaced = 0;
    for (int i = 0; i < 9; i++) {
        if (s.state[i] != 0) {
            if (s.state[i] != i+1) misplaced++;
        }
    }
    return misplaced;
}

int Puzzle::manhattan_distance(State s) { //Heuristic based on sum of displacement in terms of rows and cols across all tiles (not including blank)
    int distance = 0;
    for (int i = 0; i < 9; i++) {
        if (s.state[i] != 0) {
            distance+=(abs((s.state[i]-1)/3 - i/3)); //Add distance from proper row
            distance+=(abs((s.state[i]-1)%3 - i%3)); //Add distance from proper column
        }
    }
    return distance;
}




State Puzzle::solve(int algorithm) {
    //Evaluate initial state heuristic, add to queue
    if (algorithm == 1) {
        initial.heuristic = misplaced_tile(initial);
    } else if (algorithm == 2) {
        initial.heuristic = manhattan_distance(initial);
    } else {
        initial.heuristic = 0; //Uniform Cost Search, h(n) = 0
    }
    pq.push(initial);

    while(true) { //Repeat while there are still nodes in the queue
        if (pq.empty()) return State{0, 0, 0, 0, 0, 0, 0, 0, 0}; //No solution
        if (pq.size() > max_queue) { //Update max nodes in queue
            max_queue = pq.size();
        }
        State current = pq.top(); //Get node with lowest estimated distance
        pq.pop();
        cout << "The best state to expand, with g(n) = " << current.depth << " and h(n) = " << current.heuristic << " is:" << endl;
        cout << "[ " << current.state[0] << " " << current.state[1] << " " << current.state[2] << " ]" << endl;
        cout << "[ " << current.state[3] << " " << current.state[4] << " " << current.state[5] << " ]" << endl;
        cout << "[ " << current.state[6] << " " << current.state[7] << " " << current.state[8] << " ]" << endl << endl;
        if (goal(current)) { //Test if current state is goal state
            return current;
        }
        expand(current, algorithm); //Get current node's children, evaluate them and insert into queue
        nodes_expanded++; //Update number of nodes expanded

    }


}