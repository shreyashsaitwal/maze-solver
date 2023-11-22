#include "maze.h"

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

void Maze::solve() {}

int Maze::manhattan_distance(Position pos1, Position pos2) {
    int x = abs(get<0>(pos1) - get<0>(pos2));
    int y = abs(get<1>(pos1) - get<1>(pos2));
    return x + y;
}

vector<tuple<Position, Action>> Maze::possible_moves(Position pos) {
    vector<tuple<Position, Action>> result;
    int row = get<0>(pos);
    int col = get<1>(pos);

    if (row > 0 && !this->walls[row - 1][col]) {
        result.push_back(make_tuple(make_tuple(row - 1, col), Action::UP));
    }
    if (row < get<0>(this->dimensions) - 1 && !this->walls[row + 1][col]) {
        result.push_back(make_tuple(make_tuple(row + 1, col), Action::DOWN));
    }
    if (col > 0 && !this->walls[row][col - 1]) {
        result.push_back(make_tuple(make_tuple(row, col - 1), Action::LEFT));
    }
    if (col < get<1>(this->dimensions) - 1 && !this->walls[row][col + 1]) {
        result.push_back(make_tuple(make_tuple(row, col + 1), Action::RIGHT));
    }

    return result;
}
