#include "automata.h"

#include <iostream>
#include <map>

Automata::Automata(const std::vector<std::string> wordsDictionary)
    : start(nullptr)
{
    std::vector<State> tempStates(240);
    std::string previousWord = "";
    std::string currentWord = wordsDictionary[0];

    for (const std::string &word : wordsDictionary) {

        currentWord = word;

        size_t j = 0;

        while(previousWord[j] && currentWord[j] && previousWord[j] == currentWord[j] ){
            ++j;
        }

        size_t prefixLenghtPlusOne =  j + 1;

        for (size_t i = previousWord.length() ; i >= prefixLenghtPlusOne ; --i) {

            int minimalState = findMinimized(tempStates[i]);

            tempStates[i-1].setTransition(previousWord[i-1], minimalState);
        }

        for (size_t i = prefixLenghtPlusOne ; i <= currentWord.length() ; ++i) {

            tempStates[i].clear();

            tempStates[i-1].setTransition(currentWord[i-1], -1);
        }

        tempStates[currentWord.length()].setFinal(true);

        previousWord = currentWord;
    }

    for (size_t i = currentWord.length() ; i >= 1; --i){
        int minimalState = findMinimized(tempStates[i]);
        tempStates[i-1].setTransition(currentWord[i-1], minimalState);
    }

    initialState = findMinimized(tempStates[0]);
    start = &states[initialState];

    tempStates.clear();
    stateDictionary.clear();

}

void Automata::printInfo()
{
    int br = 0;
    std::vector<bool> reachable;
    reachable.resize(states.size());
    printw(initialState,br,reachable);

    int r = 0;
    for (bool b : reachable) {
        r+=b;
    }

    std::cout << "total words in automata : " <<br << "\nreachable states " << r+1 <<" \\ "<<states.size()<<std::endl ;
}

std::shared_ptr<Automata::StringList> Automata::find(const std::string &prefix) const
{
    std::shared_ptr<Automata::StringList> words = std::make_shared<Automata::StringList>();

    if (prefix.length() == 0) {
        return words;
    }

    int state = initialState;

    for (char ch : prefix) {
        state = states[state].getTransition(ch);
        if (state == -1) {
            return words;
        }
    }

    dfs(state, prefix, words);

    return words;
}

void Automata::setNumOfWords(unsigned number)
{
    numOfWords = number;
}

void Automata::printw(int state, int &br, std::vector<bool> &reachable)
{
    if (states[state].ifFinal()){
        ++br;
    }

    const std::map<char, int> &transition = states[state].getTransitions();
    for(auto it : transition) {
        reachable[it.second] = true;
        printw(it.second, br,reachable);
    }
}

bool Automata::dfs(int state, const std::string prefix, std::shared_ptr<Automata::StringList> words) const
{
    if (states[state].ifFinal()){
        words->push_back(prefix);
        if (words->size() == numOfWords){
            return true;
        }
    }

    const std::map<char, int> &transition = states[state].getTransitions();
    for(auto it : transition) {
        if (dfs(it.second, prefix + it.first ,words)){
            return true;
        }
    }

    return  false;
}

int Automata::findMinimized(const State &state) {

    auto it = stateDictionary.find({state,-1});

    if (it == stateDictionary.end()) {
        states.push_back(state);
        StatePair newPair = {state,states.size()-1};
        stateDictionary.insert(newPair);
        return newPair.second;
    }

    return it->second;
}
