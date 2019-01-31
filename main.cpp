#include "mainwindow.h"
#include <QApplication>

#include "automata.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <ctime>
#include <memory>


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
    Automata automa(words);
    time(&end);

    words.clear();

    automa.setNumOfWords(10);

    std::cout<<"build\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    automa.printInfo();

    std::cout<<"READY"<<std::endl;

    MainWindow w(&automa);
    w.show();

    return a.exec();
}
