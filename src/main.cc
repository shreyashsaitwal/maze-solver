#include <iostream>

#include "maze.h"
#include "utils.h"

using namespace std;

int main() {
    auto maze = Maze(Utils::read_file("../mazes/maze1.txt"));
    maze.solve();
    maze.print_solution();
}
