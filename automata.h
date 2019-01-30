#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <set>
#include <vector>
#include <string>
#include <list>
#include <utility>

class Automata
{
private:

    using StatePair = std::pair<State,int>;

    struct Compare{
        bool operator()(const StatePair &p1, const StatePair &p2){
            return State::Compare()(p1.first, p2.first) < 0;
        }
    };
public:
    Automata(const std::vector<std::string> wordsDictionary);
    void print();
    void printw(State *root, std::string word, int &br, std::vector<bool> &reachable);

private:
    int findMinimized(const State &state);

private:
    std::set<StatePair,Compare> stateDictionary;
    std::vector<State> states;
    State *start;
    size_t initialState;

};

#endif // AUTOMATA_H
