#include <iostream>
#include <queue>

#include "puzzle.h"

using namespace std;

//Default 8-puzzles
int trivial[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
int veryEasy[] = {1, 2, 3, 4, 5, 6, 7, 0, 8};
int easy[] = {1, 2, 0, 4, 5, 3, 7, 8, 6};
int doable[] = {0, 1, 2, 4, 5, 3, 7, 8, 6};
int oh_boy[] = {8, 7, 1, 6, 0, 2, 5, 4, 3};
int impossible[] = {8, 6, 7, 2, 5, 4, 3, 0, 1};


Puzzle init_default_puzzle() {
    while (1) {
        cout << "Please enter the desired difficulty of the default puzzle, on a scale from 0 to 5.\n";

        int difficulty;
        cin >> difficulty;

        if (difficulty == 0) {
            cout << "Difficulty 'Trivial' selected.\n";
            return Puzzle{trivial};
        } else if (difficulty == 1) {
            cout << "Difficulty 'Very Easy' selected.\n";
            return Puzzle{veryEasy};
        } else if (difficulty == 2) {
            cout << "Difficulty 'Easy' selected.\n";
            return Puzzle{easy};
        } else if (difficulty == 3) {
            cout << "Difficulty 'Doable' selected.\n";
            return Puzzle{doable};
        } else if (difficulty == 4) {
            cout << "Difficulty 'Oh Boy' selected.\n";
            return Puzzle{oh_boy};
        } else if (difficulty == 5) {
            cout << "Difficulty 'Impossible' selected.\n";
            return Puzzle{impossible};
        }

    }

}

//Print final result
void print(Puzzle puzzle, State end) {
    State init = puzzle.getInitial();

    cout << "[ " << init.state[0] << " " << init.state[1] << " " << init.state[2] << " ]" << endl;
    cout << "[ " << init.state[3] << " " << init.state[4] << " " << init.state[5] << " ]" << endl;
    cout << "[ " << init.state[6] << " " << init.state[7] << " " << init.state[8] << " ]" << " ->" << endl << endl;

    cout << "[ " << end.state[0] << " " << end.state[1] << " " << end.state[2] << " ]" << endl;
    cout << "[ " << end.state[3] << " " << end.state[4] << " " << end.state[5] << " ]" << endl;
    cout << "[ " << end.state[6] << " " << end.state[7] << " " << end.state[8] << " ]" << endl << endl;

    cout << "Depth: " << end.depth << endl;
    cout << "Nodes expanded: " << puzzle.getMaxExpanded() << endl;
    cout << "Max nodes in queue: " << puzzle.getMaxQueue() << endl;
}

void select_init_algorithm(Puzzle puzzle) {
    while (1) {
        cout << "Please select an algorithm: (1) Uniform Cost Search, (2) A* with Misplaced Tile Heuristic, or (3) A* with Manhattan Distance Heuristic.\n";

        int algorithm;
        cin >> algorithm;

        if (algorithm == 1) {
            State end = puzzle.solve(0);
            print(puzzle, end);
            return;

        } else if (algorithm == 2) {
            State end = puzzle.solve(1);
            print(puzzle, end);
            return;

        } else if (algorithm == 3) {
            State end = puzzle.solve(2);
            print(puzzle, end);
            return;

        }
    }

}


int main() {
    cout << "Welcome to the 8-puzzle solver. Enter '1' to use a default puzzle, or enter '2' to create your own.\n";

    int mode;
    cin >> mode;

    if (mode == 1) {
        select_init_algorithm(init_default_puzzle());
    } else if (mode == 2) {
        cout << "Enter your puzzle row by row, using a 0 to represent the blank. Use a space to delimit the numbers. Please only enter valid 8-puzzles. Hit Enter when finished.\n";
        int puzzle[9];

        int num;
        cout << "Enter the first row: ";
        for (int i = 0; i < 3; i++) {
            cin >> num;
            puzzle[i] = num;
        }
        cout << "Enter the second row: ";
        for (int i = 3; i < 6; i++) {
            cin >> num;
            puzzle[i] = num;
        }
        cout << "Enter the third row: ";
        for (int i = 6; i < 9; i++) {
            cin >> num;
            puzzle[i] = num;
        }

        Puzzle p(puzzle);
        select_init_algorithm(p);

    }

    return 0;
}