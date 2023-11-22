#include <iostream>

#include "maze.h"
#include "utils.h"

using namespace std;

int main() {
    auto maze = Maze(Utils::read_file("D:/College/sy/fds/maze-solver/mazes/maze1.txt"));
    cout << to_string(maze.dimensions) << endl;
    cout << to_string(maze.start) << endl;
    cout << to_string(maze.goal) << endl;
}