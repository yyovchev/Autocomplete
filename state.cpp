#include "state.h"

void State::setTransition(char ch, int state){
    transition[ch] = state;
}

void State::setFinal(bool final) {
    this->final = final;
}

void State::clear(){
    transition.clear();
    final = false;
}

int State::getTransition(char ch) const
{
    auto it = transition.find(ch);
    return (it == transition.end()) ? -1 : it->second;
}

bool State::hasTransition(char ch) const
{
    return getTransition(ch) != -1;
}

std::string State::getKey() const
{
   std::string key;

   key += (final) ? 't' : 'f';

    for (auto it : transition) {
        key += it.first;
    }

    return key;
}

const std::map<char, int> &State::getTransitions() const
{
    return transition;
}

bool State::ifFinal() const
{
    return final;
}

