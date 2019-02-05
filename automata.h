#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <set>
#include <vector>
#include <string>
#include <utility>
#include <memory>
#include <list>
#include <map>

class Automata
{
public:

    using StringList = std::list<std::string>;

    Automata(const std::vector<std::string> wordsDictionary);
    void printInfo();
    void setNumOfWords(unsigned number);
    std::shared_ptr<StringList> find(const std::string &prefix) const;
    void addWord(const std::string &word);

private:
    int findMinimized(const State &state);
    void printw(int state, int &br, std::vector<bool> &reachable);
    bool dfs(int state, const std::string prefix, std::shared_ptr<StringList> words) const;

private:
    std::map<StateDataRepresentation, int , StateDataRepresentation::Comparator> stateDictionary;
    std::vector<State> states;
    int initialState;
    unsigned numOfWords;

};

#endif // AUTOMATA_H
