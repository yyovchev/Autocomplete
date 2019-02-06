#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "automata.h"

#define SPEED_TEST 0

#if SPEED_TEST == 1
#include <chrono>
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<std::string> words;

    std::ifstream infile("words.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.size() > 3) {
            words.push_back(line);
        }
    }

#if SPEED_TEST == 1
    std::cout <<"words in dictionary - "<<words.size()<<std::endl;
    auto start = std::chrono::steady_clock::now();
#endif

    std::sort(words.begin(),words.end());

    Automata atomata(words);

#if SPEED_TEST == 1
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout <<"total time to build - "<< std::chrono::duration <double, std::milli> (diff).count() / 1000<< " s" << std::endl;

    atomata.printInfo();
#endif

    words.clear();

    MainWindow m(&atomata);
    m.show();


    return a.exec();
}
