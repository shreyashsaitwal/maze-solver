#include "utils.h"

#include <fstream>
#include <iostream>
#include <sstream>

string Utils::read_file(string file_path) {
    ifstream input_file(file_path);
    if (!input_file.is_open()) {
        cerr << "Error opening the file: " << file_path << endl;
        return "";
    }
    stringstream buf;
    buf << input_file.rdbuf();
    return buf.str();
}

vector<string> Utils::split_str(const string &input, const string &delimiter) {
    vector<string> result;

    if (delimiter.empty()) {
        for (char ch : input) {
            result.push_back(string(1, ch));
        }
        return result;
    }

    int start = 0;
    int end = input.find(delimiter);

    while (end != string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + delimiter.length();
        end = input.find(delimiter, start);
    }

    if (start < input.length()) {
        result.push_back(input.substr(start));
    }

    return result;
}

void Utils::move_up_by(int n) {
    cout << "\033[" << n << "A";
}
