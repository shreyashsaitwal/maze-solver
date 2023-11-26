#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <tuple>
#include <vector>

using namespace std;

typedef tuple<int, int> Position;
typedef tuple<int, int> Dimension;

struct Node {
    Position position;
    Node *parent = nullptr;
};

class Maze {
   private:
    Position start;
    Position goal;
    Dimension dimensions;
    vector<vector<bool>> walls;
    vector<Node *> explored_states;
    Node *solution;

    vector<Position> possible_moves(Position);
    static int manhattan_distance(Position, Position);
    void print_maze(vector<Position>, vector<Position>);

   public:
    Maze(string);
    void solve();
    void print_solution();
};

#endif
