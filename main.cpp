#include <iostream>
#include <vector>
#include <string>

#include "automata.h"

int main ()
{

    std::vector<std::string> words;
    words.push_back("aaaaa");
    words.push_back("aab");
    words.push_back("daac");
    Automata a(words);

    a.print();

    return 0;
}
