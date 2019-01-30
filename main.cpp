#include <iostream>
#include <vector>
#include <string>

#include "automata.h"

int main ()
{

    std::vector<std::string> words;
    words.push_back("aa");
//    words.push_back("aaaaa");
//    words.push_back("aab");
//    words.push_back("aac");
    words.push_back("b");
    words.push_back("ba");
//    words.push_back("bababa");
//    words.push_back("bc");
//    words.push_back("cb");
//    words.push_back("ccb");
//    words.push_back("db");
//    words.push_back("dab");
//    words.push_back("ddb");
//    words.push_back("hab");
//    words.push_back("hob");



    Automata a(words);

    a.print();

    return 0;
}
