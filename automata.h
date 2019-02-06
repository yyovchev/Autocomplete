#ifndef AUTOMATA_H
#define AUTOMATA_H

#include "state.h"

#include <vector>
#include <string>
#include <memory>
#include <list>
#include <unordered_map>

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
    void bfs(int &br, std::vector<bool> &reachable);
    bool dfs(int state, const std::string prefix, std::shared_ptr<StringList> words) const;

private:
    std::unordered_map<std::string, int> stateDictionary;
    std::vector<State> states;
    int initialState;
    unsigned numOfWords;

};

#endif // AUTOMATA_H
