#ifndef ENV
#define ENV

#include <unordered_map>
#include <list>
#include <string>

using namespace std;

class Environment {
private:
    unordered_map<string, string> level;
public:
    Environment();
    void update(string x, string v);
    bool check(string x);
	string  lookup(string x);
};

#endif