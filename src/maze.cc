#include "maze.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <thread>
#include <queue>
#include <unordered_set>

#include "rang.h"
#include "utils.h"

Maze::Maze(string maze_str) {
    auto lines = Utils::split_str(maze_str, "\n");

    for (int i = 0; i < lines.size(); i++) {
        vector<bool> row;
        auto chars = Utils::split_str(lines[i], "");

        for (int j = 0; j < chars.size(); j++) {
            if (chars[j] == "A") {
                this->start = make_tuple(i, j);
            } else if (chars[j] == "B") {
                this->goal = make_tuple(i, j);
            }
            row.push_back(chars[j] == "#");
        }
        this->walls.push_back(row);
    }

    this->dimensions = make_tuple(lines.size(), lines[0].size());
}

void Maze::solve(function<int(Position)> heuristic) {
    auto cmp = [](shared_ptr<Node> left, shared_ptr<Node> right) { return left->f > right->f; };
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(cmp)> frontier(cmp);
    unordered_set<Position> explored;

    shared_ptr<Node> start_node = make_shared<Node>(Node{this->start});
    start_node->h = heuristic ? heuristic(this->start) : manhattan_distance(this->start, this->goal);
    start_node->f = start_node->g + start_node->h;
    frontier.push(start_node);

    while (!frontier.empty()) {
        shared_ptr<Node> node = frontier.top();
        frontier.pop();

        if (node->position == this->goal) {
            this->solution = node;
            return;
        }

        explored.insert(node->position);
        this->explored_states.push_back(node);

        auto moves = this->possible_moves(node->position);
        for (Position pos : moves) {
            if (explored.find(pos) != explored.end()) {
                continue;
            }

            shared_ptr<Node> neighbour = make_shared<Node>(Node{pos, node});
            neighbour->g = node->g + 1;
            neighbour->h = heuristic ? heuristic(pos) : manhattan_distance(pos, this->goal);
            neighbour->f = neighbour->g + neighbour->h;

            auto is_in_frontier = any_of(frontier.c.begin(), frontier.c.end(), [&neighbour](shared_ptr<Node> n) {
                return n->position == neighbour->position;
            });

            if (!is_in_frontier) {
                frontier.push(neighbour);
            }
        }
    }
}

int Maze::a_star_heuristic(Position pos) {
    return manhattan_distance(pos, this->goal);
}

void Maze::print_solution() {
    vector<Position> sol_pos;
    if (this->solution != nullptr) {
        auto node = this->solution;
        while (node->parent != nullptr) {
            sol_pos.push_back(node->position);
            node = node->parent;
        }
    }

    vector<Position> expl_pos;
    for (auto node : this->explored_states) {
        expl_pos.push_back(node->position);
    }

    int count = 0;
    while (count < expl_pos.size()) {
        this->print_maze(vector<Position>(),
                         vector<Position>(expl_pos.begin(), expl_pos.begin() + count));
        this_thread::sleep_for(chrono::milliseconds(100));
        Utils::move_up_by(get<0>(this->dimensions));
        count++;
    }

    if (this->solution != nullptr) {
        count = 0;
        while (count < sol_pos.size()) {
            this->print_maze(vector<Position>(sol_pos.begin(), sol_pos.begin() + count), expl_pos);
            this_thread::sleep_for(chrono::milliseconds(50));
            Utils::move_up_by(get<0>(this->dimensions));
            count++;
        }
    }

    this->print_maze(sol_pos, expl_pos);
    cout << endl;

    if (this->solution != nullptr)
        cout << "Path length:     " << sol_pos.size() << endl;
    else
        cout << "No solution found" << endl;
    cout << "Explored states: " << this->explored_states.size() << endl;
}

void Maze::print_maze(vector<Position> solution_pos, vector<Position> explored_pos) {
    for (int i = 0; i < this->walls.size(); i++) {
        for (int j = 0; j < this->walls[0].size(); j++) {
            Position pos = make_tuple(i, j);
            auto is_sol_pos = any_of(solution_pos.begin(), solution_pos.end(),
                                     [&pos](Position p) { return p == pos; });
            auto is_expl_pos = any_of(explored_pos.begin(), explored_pos.end(),
                                      [&pos](Position p) { return p == pos; });

            if (pos == this->start) {
                cout << rang::fg::black << rang::bg::magenta << " A " << rang::style::reset;
            } else if (pos == this->goal) {
                cout << rang::fg::black << rang::bg::blue << " B " << rang::style::reset;
            } else if (this->walls[i][j]) {
                cout << "▓▓▓" << rang::style::reset;
            } else if (is_sol_pos) {
                cout << rang::fg::black << rang::bg::green << " • " << rang::style::reset;
            } else if (is_expl_pos) {
                cout << rang::fg::black << rang::bg::yellow << " · " << rang::style::reset;
            } else {
                cout << " · ";
            }
        }
        cout << endl;
    }
}

int Maze::manhattan_distance(Position pos1, Position pos2) {
    int x = abs(get<0>(pos1) - get<0>(pos2));
    int y = abs(get<1>(pos1) - get<1>(pos2));
    return x + y;
}

vector<Position> Maze::possible_moves(Position pos) {
    vector<Position> result;
    int row = get<0>(pos);
    int col = get<1>(pos);

    if (row > 0 && !this->walls[row - 1][col]) {
        result.push_back(make_tuple(row - 1, col));
    }
    if (row < get<0>(this->dimensions) - 1 && !this->walls[row + 1][col]) {
        result.push_back(make_tuple(row + 1, col));
    }
    if (col > 0 && !this->walls[row][col - 1]) {
        result.push_back(make_tuple(row, col - 1));
    }
    if (col < get<1>(this->dimensions) - 1 && !this->walls[row][col + 1]) {
        result.push_back(make_tuple(row, col + 1));
    }

    return result;
}
