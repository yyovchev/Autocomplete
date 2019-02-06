#include "automata.h"

#include <iostream>
#include <queue>

Automata::Automata(const std::vector<std::string> wordsDictionary)
    :numOfWords(10)
{
    std::vector<State> tempStates(240);
    std::string previousWord = "";
    std::string currentWord = wordsDictionary[0];

    for (const std::string &word : wordsDictionary) {

        currentWord = word;

        size_t prefix = 0;

        while(previousWord[prefix] && currentWord[prefix] && previousWord[prefix] == currentWord[prefix] ){
            ++prefix;
        }

        size_t prefixLenghtPlusOne =  prefix + 1;

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

    tempStates.clear();
    stateDictionary.clear();

}

void Automata::printInfo()
{
    int br = 0;
    std::vector<bool> reachable;
    reachable.resize(states.size());
    bfs(br,reachable);

    int r = 0;
    for (bool b : reachable) {
        r+=b;
    }

    std::cout << "total words in automata : " <<br << "\nreachable states " << r <<" \\ "<<states.size()<<std::endl ;
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

void Automata::addWord(const std::string &word)
{
    if (word.length() == 0){
        return;
    }

    int state = initialState;
    int prevState = state;

    for( char ch : word){
        prevState = state;
        state = states[state].getTransition(ch);

        if (state == -1) {
            states.push_back(State());
            state = states.size() - 1;

            states[prevState].setTransition(ch, state);
        }
    }

    states[state].setFinal(true);

}

void Automata::setNumOfWords(unsigned number)
{
    numOfWords = number;
}

void Automata::bfs(int &br, std::vector<bool> &reachable)
{

    int state = initialState;
    std::queue<int> currunt;

    currunt.push(state);

    while (!currunt.empty()) {
        reachable[currunt.front()] = true;

        int front = currunt.front();

        if (states[front].ifFinal()){
            ++br;
        }

        const std::map<wchar_t, int> &transition = states[front].getTransitions();
        for(auto it : transition) {
            currunt.push(it.second);
        }
        currunt.pop();
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

    const std::map<wchar_t, int> &transition = states[state].getTransitions();
    for(auto it : transition) {
        if (dfs(it.second, prefix + (char)it.first ,words)){
            return true;
        }
    }

    return  false;
}

int Automata::findMinimized(const State &state) {

    std::string key;
    state.getTransitionsAsStrings().swap(key);
    auto it = stateDictionary.find(key);

    if (it == stateDictionary.end()) {
        states.push_back(state);
        int newStatePosition = states.size() - 1;
        stateDictionary.emplace(key,newStatePosition);
        return newStatePosition;
    }

    return it->second;
}
