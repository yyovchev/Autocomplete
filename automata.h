#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <set>
#include <vector>
#include <string>
#include <list>

class Automata
{
public:
    Automata(const std::vector<std::string> words);
    void print();
    void printw(State *root,std::string word);

private:
    State* findMinimized(State *state);
    void updateState(State *from, State *to, char ch);

private:
    std::set<State*,State::PtrCompare> stateDictionary;
    std::vector<State> states;

    State *start;

};

#endif // AUTOMATA_H
