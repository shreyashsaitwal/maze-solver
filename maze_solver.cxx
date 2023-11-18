#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

enum Action { UP, DOWN, LEFT, RIGHT };

typedef tuple<int, int> Position;

struct Node {
    Position position;
    Action action;
    Node *parent;
    int path_cost = 0;
};

class Maze {
   public:
    Position start;
    Position goal;
    vector<vector<bool>> walls;
    tuple<int, int> dimensions;
    vector<Node *> explored;
    Node *solution = nullptr;

    vector<string> split_str(const string &input, const string &delimiter) {
        vector<string> result;

        // Handle the case of an empty delimiter
        if (delimiter.empty()) {
            for (char ch : input) {
                result.push_back(string(1, ch));
            }
            return result;
        }

        size_t start = 0;
        size_t end = input.find(delimiter);

        while (end != string::npos) {
            result.push_back(input.substr(start, end - start));
            start = end + delimiter.length();
            end = input.find(delimiter, start);
        }

        // Handle the case when the input string ends with the delimiter
        if (start < input.length()) {
            result.push_back(input.substr(start));
        }

        return result;
    }

    //    public:
    Maze(string maze_str) {
        auto lines = split_str(maze_str, "\n");

        for (int i = 0; i < lines.size(); i++) {
            auto chars = split_str(lines[i], "");
            vector<bool> row;
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
};

string read_file(const string &filePath) {
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "Error opening the file: " << filePath << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    inputFile.close();
    return content;
}

string to_string(tuple<int, int> tup) {
    return "(" + to_string(get<0>(tup)) + ", " + to_string(get<1>(tup)) + ")";
}

int main() {
    auto maze = Maze(read_file("maze1.txt"));
    cout << to_string(maze.dimensions) << endl;
    cout << to_string(maze.start) << endl;
    cout << to_string(maze.goal) << endl;
}
