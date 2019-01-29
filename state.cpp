#include "state.h"

void State::setTransition(char ch, State *state){
    transition[ch] = state;
}

void State::setFinal(bool final) {
    this->final = final;
}

void State::clear(){
    transition.clear();
    final = false;
}

State* State::getTransition(char ch) const
{
    auto it = transition.find(ch);
    return (it == transition.end()) ? nullptr : it->second;
}

bool State::hasTransition(char ch) const
{
    return getTransition(ch) != nullptr;
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

const std::map<char, State *> &State::getTransitions() const
{
    return transition;
}

bool State::ifFinal() const
{
    return final;
}

