#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <set>
#include <vector>
#include <string>
<<<<<<< HEAD
#include <utility>
#include <memory>
#include <list>
=======
#include <list>
#include <utility>
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

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
<<<<<<< HEAD

    using StringList = std::list<std::string>;

    Automata(const std::vector<std::string> wordsDictionary);
    void printInfo();
    void setNumOfWords(size_t number);
    std::shared_ptr<StringList> find(const std::string &prefix) const;

private:
    int findMinimized(const State &state);
    void printw(size_t state, int &br, std::vector<bool> &reachable);
    bool dfs(size_t state, const std::string prefix, std::shared_ptr<StringList> words) const;
=======
    Automata(const std::vector<std::string> wordsDictionary);
    void print();
    void printw(State *root, std::string word, int &br, std::vector<bool> &reachable);

private:
    int findMinimized(const State &state);
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

private:
    std::set<StatePair,Compare> stateDictionary;
    std::vector<State> states;
<<<<<<< HEAD
    size_t initialState;
    size_t numOfWords;
=======
    State *start;
    size_t initialState;
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

};

#endif // AUTOMATA_H
