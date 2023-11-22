#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int> Position;
typedef tuple<int, int> Dimension;

enum Action { UP, DOWN, LEFT, RIGHT };

struct Node {
    Position position;
    Action action;
    Node *parent;
    int path_cost = 0;
};

class Maze {
   private:
    vector<tuple<Position, Action>> possible_moves(Position);
    
    int manhattan_distance(Position, Position);

   public:
    // TODO: Remove public access
    Position start;
    Position goal;
    Dimension dimensions;
    vector<vector<bool>> walls;
    vector<Node *> explored;
    Node *solution = nullptr;

    Maze(string);
    void solve();
    // void print_solution();
};

#endif
