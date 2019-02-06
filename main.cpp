#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <ctime>
#include <memory>

#include<clocale>

#include "automata.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<std::string> words;

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
    Automata atomata(words);
    time(&end);

    words.clear();

    std::cout<<"build\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;


    atomata.setNumOfWords(10);

    atomata.printInfo();

    std::cout<<"END"<<std::endl;

    MainWindow m(&atomata);
    m.show();


    return a.exec();
}
