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
    Automata(const std::vector<std::string> words);
    void print();
    void printw(State *root,std::string word);

private:
    int findMinimized(const State &state);
    void updateLastCommanState(const std::string &word, const std::string debugword, int prefixLenght, State start, State tempstate);

private:
    std::set<StatePair,Compare> stateDictionary;
    std::vector<State> states;

    State *start;

};

#endif // AUTOMATA_H
