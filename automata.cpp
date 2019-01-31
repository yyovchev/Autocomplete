#include "automata.h"

#include <iostream>
<<<<<<< HEAD
#include <map>

Automata::Automata(const std::vector<std::string> wordsDictionary)
{
    std::vector<State> tempStates(240);
=======

Automata::Automata(const std::vector<std::string> wordsDictionary)
    : start(nullptr)
{
//    states.resize(1);
    std::vector<State> tempStates(240);
//    std::vector<State*> previousWordPath(240);
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28
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
<<<<<<< HEAD
=======
//            if (previousWord.length() == prefixLenghtPlusOne && i == prefixLenghtPlusOne){

//                bool isFinalState = tempStates[i].ifFinal();
//                tempStates[i].clear();
//                tempStates[i].setFinal(isFinalState);
//            }
//            else {
//                tempStates[i].clear();
//            }
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

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
<<<<<<< HEAD
=======
    start = &states[initialState];
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

    tempStates.clear();
    stateDictionary.clear();

}

<<<<<<< HEAD
void Automata::printInfo()
{

    int br = 0;
    std::vector<bool> reachable;
    reachable.resize(states.size());
    printw(initialState,br,reachable);
=======
void Automata::print()
{

//    for (size_t i = 0; i < states.size(); i++) {
//        std::cout << i<<" "<< states[i].ifFinal() << " -> ";
//        for (auto &it : states[i].getTransitions()) {
//            std::cout << (it.first) <<"("<< it.second << ") "<<", ";
//        }
//        std::cout << std::endl;
//    }

//    std::cout<<"\n\n";

    std::string word = "";
    int br = 0;
    std::vector<bool> reachable;
    reachable.resize(states.size());
    printw(start,word,br,reachable);
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

    int r = 0;
    for (bool b : reachable) {
        r+=b;
    }

    std::cout << "total words in automata : " <<br << "\nreachable states " << r+1 <<" \\ "<<states.size()<<std::endl ;
}

<<<<<<< HEAD
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

void Automata::setNumOfWords(size_t number)
{
    numOfWords = number;
}

void Automata::printw(size_t state, int &br, std::vector<bool> &reachable)
{
    if (states[state].ifFinal()){
        ++br;
    }

    const std::map<char, int> &transition = states[state].getTransitions();
    for(auto it : transition) {
        reachable[it.second] = true;
        printw(it.second,  br,reachable);
    }
}

bool Automata::dfs(size_t state, const std::string prefix, std::shared_ptr<Automata::StringList> words) const
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

=======
void Automata::printw(State *root, std::string word, int &br, std::vector<bool> &reachable)
{
    if (root->ifFinal()){
        ++br;
        //std::cout<<word <<std::endl;
    }

    for(auto it : root->getTransitions()) {
        reachable[it.second] = true;
        printw(&states[it.second], word + it.first, br,reachable);
    }
}

>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28
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
