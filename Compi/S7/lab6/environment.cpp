#include "environment.hh"


Environment::Environment() {
}

void Environment::update(string x, string v) {
    level[x] = v;
}

bool Environment::check(string x) {
    unordered_map<std::string,string>::const_iterator it = level.find(x);
    if (it == level.end())
        return false;
    else
        return true;
}

string Environment::lookup(string x) {
    unordered_map<std::string,string>::const_iterator it = level.find(x);
    if (it == level.end())
        return 0;
    else
        return it->second;
}


