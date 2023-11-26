#include <iostream>

#include "maze.h"
#include "utils.h"

using namespace std;

int main() {
    cout << "--- Welcome to Maze Solver! ---" << endl;
    cout << "Select which maze you want to solve: " << endl;
    cout << "1. Maze 1" << endl;
    cout << "2. Maze 2" << endl;
    cout << "3. Maze 3" << endl;
    cout << "4. Your own maze!" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    string maze_str;
    string maze_path;
    switch (choice) {
        case 1:
            maze_str = Utils::read_file("../mazes/maze1.txt");
            break;
        case 2:
            maze_str = Utils::read_file("../mazes/maze2.txt");
            break;
        case 3:
            maze_str = Utils::read_file("../mazes/maze3.txt");
            break;
        case 4:
            cout << "Enter path to your maze.txt file: ";
            cin >> maze_path;
            maze_str = Utils::read_file(maze_path);
            break;
        default:
            cout << "Invalid choice!" << endl;
            return 1;
    }

    Maze maze(maze_str);
    maze.solve();
    maze.print_solution();
}
