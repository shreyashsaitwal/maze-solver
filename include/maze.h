#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <functional>

using namespace std;

typedef tuple<int, int> Position;
typedef tuple<int, int> Dimension;

struct Node {
    Position position;
    shared_ptr<Node> parent = nullptr;
    int g = 0; // Cost from start to this node
    int h = 0; // Heuristic cost from this node to goal
    int f = 0; // Total cost (g + h)
};

class Maze {
   private:
    Position start;
    Position goal;
    Dimension dimensions;
    vector<vector<bool>> walls;
    vector<shared_ptr<Node>> explored_states;
    shared_ptr<Node> solution = nullptr;

    vector<Position> possible_moves(Position);
    static int manhattan_distance(Position, Position);
    void print_maze(vector<Position>, vector<Position>);

   public:
    Maze(string);
    void solve(function<int(Position)> heuristic = nullptr);
    int a_star_heuristic(Position);
    void print_solution();
};

#endif
