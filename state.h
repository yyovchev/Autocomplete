#ifndef STATE_H
#define STATE_H

#include <map>
#include <string>
#include <functional>

class State {
public:

    struct Compare {
        int operator()(const State &s1, const State &s2) {

            if (s1.final ^ s2.final) {
                return (s1.final) ? 1 : -1;
            }

            size_t size_s1 = s1.transition.size();
            size_t size_s2 = s2.transition.size();

            if (size_s1 == 0 && size_s2 == 0) {
                return true;
            }
            else if (size_s1 != size_s2) {
                return  (size_s1 > size_s2) ? 1 : -1;
            }

            auto iter_1 = s1.transition.cbegin(), iter_2 = s2.transition.cbegin();
            auto end_1 = s1.transition.cend(), end_2 = s2.transition.cend();

            for (; iter_1 != end_1 && iter_2 != end_2 ; ++iter_1 , ++iter_2 ) {
                if (iter_1->first != iter_2->first) {
                    return (iter_1->first > iter_2->first) ? 1 : -1;
                }
                else if (iter_1->second != iter_2->second) {
                    return (iter_1->second > iter_2->second) ? 1 : -1;
                }
            }

            return 0;
        }
    };

public:
    State(bool isFinal = false);
    void setTransition(wchar_t ch, int state);
    void setFinal(bool final);
    void clear();
    int getTransition(wchar_t ch) const;
    bool hasTransition(wchar_t ch) const;
    std::string getTransitionsAsStrings() const;
    const std::map<wchar_t, int> &getTransitions() const;
    bool ifFinal() const;

    bool operator ==(const State &state) const;

private:
    std::map<wchar_t, int> transition;
    bool final;

};

class StateDataRepresentation {
public:
    struct Comparator{
        bool operator()(const StateDataRepresentation &s1,
                        const StateDataRepresentation &s2){
            if (s1.hash != s2.hash){
                return  s1.hash < s2.hash;
            }

            return s1.statesTransitions.compare(s2.statesTransitions) > 0;
        }
    };

public:
    StateDataRepresentation(const State &state){
        statesTransitions = state.getTransitionsAsStrings();
        hash = std::hash<std::string>{}(statesTransitions);
    }

private:
    size_t hash;
    std::string statesTransitions;
};

#endif // STATE_H
