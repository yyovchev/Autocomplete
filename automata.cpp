#include "automata.h"

#include <iostream>

Automata::Automata(const std::vector<std::string> words)
    : start(nullptr)
{
    states.push_back(State());
    std::vector<State> tempStates(240);
    std::vector<State*> previousWordPath(240);
    std::string previousWord = "";
    std::string currentWord = words[0];

//    for (size_t j = 0; j < currentWord.length() ; ++j) {
//        tempStates[j+1].clear();
//        tempStates[j].setTransition(currentWord[j], -1);
//    }
    tempStates[currentWord.length()].setFinal(true);

    for (size_t j = currentWord.length(); j > 0 ; --j) {
        tempStates[j-1].setTransition(currentWord[j-1], findMinimized(tempStates[j]));
    }


    for (size_t i = 1;  i < words.size(); i++) {
        previousWord = currentWord;
        currentWord = words[i];

        size_t j = 0;
        while ( j < currentWord.length()  &&
                j < previousWord.length() &&
                previousWord[j] == currentWord[j])
        {
            ++j;
        }

        size_t prefixLenght = j;


        size_t lastCommanState = 0;
        states[0]= tempStates[0];
//        int reg = (prefixLenght == previousWord.length()) ? 1 : 0;

        int reg = 0;
        for(size_t j = 0 ; j < prefixLenght ; ++j) {
            lastCommanState = states[lastCommanState].getTransition(previousWord[j]);
        }

        if (prefixLenght == previousWord.length()) {

            auto it = stateDictionary.find({states[lastCommanState],-1});

            std::cout<<it->second<<"  ";

            if (it != stateDictionary.end()){
                stateDictionary.erase(it);
            }

            states[lastCommanState].setTransition(currentWord[prefixLenght],-1);

            auto check = stateDictionary.insert({states[lastCommanState],lastCommanState});

            if (check.second == true){
                std::cout<<"update with temp value\n";
            }
            else {
             std::cout<<"exists! ;((((())))) \n";
            }
        }



        for (size_t j = prefixLenght; j < currentWord.length() ; ++j) {
            if (j) {
                tempStates[j].clear();
            }
//            tempStates[j].setTransition(currentWord[j], -1);
        }
        tempStates[currentWord.length()].clear();
        tempStates[currentWord.length()].setFinal(true);

        for (size_t j = currentWord.length(); j >= prefixLenght +1 ; --j) {
            int minimalForTempTransition = findMinimized(tempStates[j]);
            tempStates[j-1].setTransition(currentWord[j-1], minimalForTempTransition);

            std::cout<<"for final foudn " <<minimalForTempTransition << std::endl;

        }

            auto it = stateDictionary.find({states[lastCommanState],-1});

            if (it != stateDictionary.end()){
                std::cout<<"delete\n";
                stateDictionary.erase(it);
            }

            std::cout<<"\n-------------\n" << std::endl;

            std::cout<<previousWord << "("<<previousWord.length()<<") -> ("<<previousWord.length()<<")" << currentWord<<std::endl;

            std::cout <<"prefix : "<<prefixLenght << "\nlast comman state : "<<lastCommanState<<"\nchar : "<<currentWord[prefixLenght - reg]<<std::endl;
            for (auto &it : states[lastCommanState].getTransitions()) {
                std::cout << (it.first) <<"("<< it.second << ") "<<", ";
            }
            std::cout<< std::endl;

//            int minimalState = findMinimized(tempStates[prefixLenght - reg + 1 ]);
            int minimalState = tempStates[prefixLenght].getTransition(currentWord[prefixLenght]);

            states[lastCommanState].setTransition(currentWord[prefixLenght - reg],minimalState);
            std::cout <<"found state : " <<minimalState<< std::endl;

            for (auto &it : states[lastCommanState].getTransitions()) {
                std::cout << (it.first)<<"("<< it.second << ") "<<", ";
            }
            std::cout<<"\n-------------\n" << std::endl;

            auto check = stateDictionary.insert({states[lastCommanState],lastCommanState});
            if (check.second == true){
                std::cout<<"new ell added\n";
            }
            else {
             std::cout<<"exists! \n";
            }
    }

    states[0] = tempStates[0];
    start = &states[0];
}

void Automata::print()
{
    for (size_t i = 0; i < states.size(); i++) {
        std::cout << i<<" "<< states[i].ifFinal() << " -> ";
        for (auto &it : states[i].getTransitions()) {
            std::cout << (it.first) <<"("<< it.second << ") "<<", ";
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
        printw(&states[it.second], word + it.first);
    }
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

void Automata::updateLastCommanState(const std::string &word, const std::string debugword, int prefixLenght, State start, State tempstate)
{
    size_t lastCommanState = 0;
    states[0]= start;


    for(size_t j = 0 ; j < prefixLenght ; ++j) {
        lastCommanState = states[lastCommanState].getTransition(word[j]);
    }


        stateDictionary.erase({states[lastCommanState],lastCommanState});

        std::cout<<"\n-------------\n" << std::endl;

        std::cout<<word << " -> " << debugword<<std::endl;

        std::cout <<"prefix : "<<prefixLenght << "\nlast comman state : "<<lastCommanState<<"\n";
        for (auto &it : states[lastCommanState].getTransitions()) {
            std::cout << (it.first) <<"("<< it.second << ") "<<", ";
        }
        std::cout<< std::endl;

        states[lastCommanState].setTransition(word[prefixLenght],
                                       findMinimized(tempstate));
        for (auto &it : states[lastCommanState].getTransitions()) {
            std::cout << (it.first) <<"("<< it.second << ") "<<", ";
        }
        std::cout<<"\n-------------\n" << std::endl;

        stateDictionary.insert({states[lastCommanState],lastCommanState});
}
