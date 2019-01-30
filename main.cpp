#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <ctime>



#include "automata.h"

int main ()
{

    std::vector<std::string> words;
//    words.push_back("aaa");
//    words.push_back("aaaaa");
//    words.push_back("baaaaa");
//    words.push_back("bababaaa");
//    words.push_back("cvfrs");
//    words.push_back("aaa");
//    words.push_back("aab");
//    words.push_back("baa");
//    words.push_back("bab");
//    words.push_back("caadsddc");
//    words.push_back("cdadsb");
//    words.push_back("dafefwefdba");
//    words.push_back("dbdsdsadbababa");
//    words.push_back("fadsadsadbc");
//    words.push_back("fsdadasdsacb");
//    words.push_back("mafdsfsdfccb");
//    words.push_back("mbdasdsadb");
//    words.push_back("mvasdsadab");
//    words.push_back("zaddsdsddb");
//    words.push_back("zbfdsfdshab");
//    words.push_back("zxfsdfdhob");


    std::ifstream infile("words.txt");

    time_t begin,end;

    time (&begin);
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.size() > 3) {
            words.push_back(line);
        }
    }
    time(&end);
    std::cout<<"words in dictionary : " << words.size()<<std::endl;


    std::cout<<"reading\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    time (&begin);
    std::sort(words.begin(),words.end());
    time(&end);

    std::cout<<"sort\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    time (&begin);
    Automata a(words);
    time(&end);

    words.clear();

    std::cout<<"build\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    a.print();

    std::cout<<"END"<<std::endl;

    std::cin.get();


    return 0;
}
