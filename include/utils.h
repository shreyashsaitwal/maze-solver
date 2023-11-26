#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <tuple>
#include <vector>

using namespace std;

string to_string(tuple<int, int>);

class Utils {
   public:
    static string read_file(const string);
    static vector<string> split_str(const string &, const string &);
    static void move_up_by(int);
};

#endif
