#include <iostream>
#include <vector>
#include <string>

#include "automata.h"

int main ()
{

    std::vector<std::string> words;
//    words.push_back("aaa");
//    words.push_back("aaaaa");
//    words.push_back("baaaaa");
//    words.push_back("bababaaa");
//    words.push_back("cvfrs");
    words.push_back("aaa");
    words.push_back("aab");
    words.push_back("baa");
    words.push_back("bab");
    words.push_back("caadsddc");
    words.push_back("cdadsb");
    words.push_back("dafefwefdba");
    words.push_back("dbdsdsadbababa");
    words.push_back("fadsadsadbc");
    words.push_back("fsdadasdsacb");
    words.push_back("mafdsfsdfccb");
    words.push_back("mbdasdsadb");
    words.push_back("mvasdsadab");
    words.push_back("zaddsdsddb");
    words.push_back("zbfdsfdshab");
    words.push_back("zxfsdfdhob");



    Automata a(words);

    a.print();


    std::cout<<"must be " << words.size()<<std::endl;

    return 0;
}
