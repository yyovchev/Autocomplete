#include "state.h"

State::State(bool isFinal)
    : final(isFinal)
{

}

void State::setTransition(wchar_t ch, int state){
    transition[ch] = state;
}

void State::setFinal(bool final) {
    this->final = final;
}

void State::clear(){
    transition.clear();
    final = false;
}

int State::getTransition(wchar_t ch) const
{
    auto it = transition.find(ch);
    return (it == transition.end()) ? -1 : it->second;
}

bool State::hasTransition(wchar_t ch) const
{
    return getTransition(ch) != -1;
}

std::string State::getTransitionsAsStrings() const
{
   std::string key;

   key += (final) ? 't' : 'f';

    for (auto it : transition) {
        key += it.first;
        key += std::to_string(it.second);
    }

    return key;
}

const std::map<wchar_t, int> &State::getTransitions() const
{
    return transition;
}

bool State::ifFinal() const
{
    return final;
}

