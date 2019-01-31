#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <set>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <list>

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

    using StringList = std::list<std::string>;

    Automata(const std::vector<std::string> wordsDictionary);
    void printInfo();
    void setNumOfWords(size_t number);
    std::shared_ptr<StringList> find(const std::string &prefix) const;

private:
    int findMinimized(const State &state);
    void printw(size_t state, int &br, std::vector<bool> &reachable);
    bool dfs(size_t state, const std::string prefix, std::shared_ptr<StringList> words) const;

private:
    std::set<StatePair,Compare> stateDictionary;
    std::vector<State> states;
    size_t initialState;
    size_t numOfWords;

};

#endif // AUTOMATA_H
