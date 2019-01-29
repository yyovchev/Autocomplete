#include "automata.h"

#include <iostream>

Automata::Automata(const std::vector<std::string> words)
    : start(nullptr)
    , states(1000000)
{
    states.push_back(State());
    std::vector<State> tempStates(240);
    std::vector<State*> previousWordPath(240);
    std::string previousWord = "";
    std::string currentWord = words[0];

    for (size_t j = 0; j < currentWord.length() ; ++j) {
        tempStates[j+1].clear();
        tempStates[j].setTransition(currentWord[j], &tempStates[j+1]);
    }
    tempStates[currentWord.length()].setFinal(true);

    for (size_t j = currentWord.length(); j > 0 ; --j) {
        tempStates[j-1].setTransition(currentWord[j-1], findMinimized(&tempStates[j]));
    }


    for (size_t i = 1;  i < words.size(); i++) {
        previousWord = currentWord;
        currentWord = words[i];

        size_t j = 0;
        while ( j < currentWord.length()  &&
                j < previousWord.length() &&
                previousWord[i] == currentWord[j])
        {
            ++j;
        }

        size_t prefixLenght = j;

        for (size_t j = prefixLenght; j < currentWord.length() ; ++j) {
            if (j) {
                tempStates[j].clear();
            }
            tempStates[j].setTransition(currentWord[j], &tempStates[j+1]);
        }
        tempStates[currentWord.length()].clear();
        tempStates[currentWord.length()].setFinal(true);

        for (size_t j = currentWord.length(); j > prefixLenght +1 ; --j) {
            tempStates[j-1].setTransition(currentWord[j-1], findMinimized(&tempStates[j]));

        }

        State *lastCommanState = &tempStates[0];

        for(size_t j = 0 ; j < prefixLenght ; ++j) {
            lastCommanState = lastCommanState->getTransition(previousWord[j]);
        }

        stateDictionary.erase(lastCommanState);
        lastCommanState->setTransition(currentWord[prefixLenght],
                                       findMinimized(&tempStates[prefixLenght+1]));
        stateDictionary.insert(lastCommanState);

    }

    states[0] = tempStates[0];
    start = &states[0];
}

void Automata::print()
{
    for (size_t i = 0; i < states.size(); i++) {
        std::cout << i << " -> ";
        for (auto &it : states[i].getTransitions()) {
            std::cout << (it.first) <<"("<< it.second - start << ") "<<", ";
        }
        std::cout << std::endl;
    }

    std::cout<<"\n\n";

    std::string word = "";
    printw(start,word);

}

void Automata::printw(State *root, std::string word)
{
    if (root->ifFinal())
        std::cout<<word <<std::endl;

    for(auto it : root->getTransitions()) {
        printw(it.second, word + it.first);
    }
}

State* Automata::findMinimized(State *state) {

    auto it = stateDictionary.find(state);

    if (it == stateDictionary.end()) {
        states.push_back(*state);
        State *newState = &(states.back());
        stateDictionary.insert(newState);
        return newState;
    }

    return *it;
}

void Automata::updateState(State *from, State *to, char ch)
{
    auto it = stateDictionary.find(from);

    if (it != stateDictionary.end()) {
        State *tempState = *it;
        stateDictionary.erase(it);
        tempState->setTransition(ch,findMinimized(to));
        stateDictionary.insert(tempState);
    }

}
