#ifndef STATE_H
#define STATE_H

#include <map>
#include <string>

class State {
public:

    struct Compare {
        int operator()(const State &s1, const State &s2) {

            if (s1.final ^ s2.final) {
                return (s1.final) ? 1 : -1;
            }

            auto iter_1 = s1.transition.cbegin(), iter_2 = s2.transition.cbegin();
            auto end_1 = s1.transition.cend(), end_2 = s2.transition.cend();

            for (; iter_1 != end_1 && iter_2 != end_2 ; ++iter_1 , ++iter_2 ) {
                if (iter_1->first != iter_2->first) {
                    return (iter_1->first > iter_2->first) ? 1 : -1;
                }
                else if (iter_1->first != iter_2->first) {
                    return (iter_1->second > iter_2->second) ? 1 : -1;
                }
            }

            return 0;
        }
    };

    struct PtrCompare {
        int operator()(State *s1_ptr, State *s2_ptr) {

            if (!s1_ptr && !s2_ptr){
                return 0;
            }
            else if (!s1_ptr ^ !s2_ptr){
                return s1_ptr ? 1 : -1;
            }

            const State &s1 = *s1_ptr;
            const State &s2 = *s2_ptr;

            return Compare()(s1, s2);

        }
    };

public:
    void setTransition(char ch, State *state);
    void setFinal(bool final);
    void clear();
    State* getTransition(char ch) const;
    bool hasTransition(char ch) const;
    std::string getKey() const;
    const std::map<char, State *> &getTransitions() const;
    bool ifFinal() const;

    bool operator ==(const State &state) const;

private:
    std::map<char, State*> transition;
    bool final;


};
#endif // STATE_H
