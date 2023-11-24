#include "maze.h"

#include <algorithm>
#include <iostream>
// #include <termcolor/termcolor.hpp>

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

void Maze::solve() {
    vector<Node *> frontier;
    frontier.push_back(new Node{this->start});

    while (!frontier.empty()) {
        if (frontier.size() > 1) {
            sort(frontier.begin(), frontier.end(), [this](Node *n1, Node *n2) {
                return Maze::manhattan_distance(this->goal, n1->position) >
                       Maze::manhattan_distance(this->goal, n2->position);
            });
        }

        auto node = frontier.back();
        frontier.pop_back();

        if (node->position == this->goal) {
            this->solution = node;
            return;
        }

        this->explored.push_back(node);

        auto moves = this->possible_moves(node->position);
        for (Position pos : moves) {
            auto neighbour = new Node{pos, node};
            auto is_explored =
                any_of(this->explored.begin(), this->explored.end(),
                       [&neighbour](Node *n) { return n->position == neighbour->position; });
            auto is_in_frontier = any_of(frontier.begin(), frontier.end(), [&neighbour](Node *n) {
                return n->position == neighbour->position;
            });
            if (!is_explored && !is_in_frontier) {
                frontier.push_back(neighbour);
            }
        }
    }
}

void Maze::print_solution() {
    vector<Position> sol_pos;
    auto node = this->solution;
    while (node->parent != nullptr) {
        sol_pos.push_back(node->position);
        node = node->parent;
    }

    for (int i = 0; i < this->walls.size(); i++) {
        for (int j = 0; j < this->walls[0].size(); j++) {
            Position pos = make_tuple(i, j);
            auto is_sol_path =
                any_of(sol_pos.begin(), sol_pos.end(), [&pos](Position p) { return p == pos; });
            if (pos == this->start) {
                cout << "A";
                // cout << termcolor::black << termcolor::on_purple << " A " << termcolor::reset;
            } else if (pos == this->goal) {
                cout << "B";
                // cout << termcolor::black << termcolor::on_cyan << " B " << termcolor::reset;
            } else if (this->walls[i][j]) {
                cout << "#";
                // cout << termcolor::on_bright_black << "   " << termcolor::reset;
            } else if (is_sol_path) {
                cout << "+";
                // cout << termcolor::on_green << "   " << termcolor::reset;
            } else {
                cout << " ";
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
