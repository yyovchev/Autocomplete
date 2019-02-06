#ifndef STATE_H
#define STATE_H

#include <map>
#include <string>
#include <functional>

class State {
public:
public:
    State(bool isFinal = false);

    void setTransition(wchar_t ch, int state);
    void setFinal(bool final);
    void clear();

    const std::map<wchar_t, int> &getTransitions() const;
    int getTransition(wchar_t ch) const;
    bool hasTransition(wchar_t ch) const;
    std::string getTransitionsAsStrings() const;
    bool ifFinal() const;

private:
    std::map<wchar_t, int> transition;
    bool final;

};

#endif // STATE_H
