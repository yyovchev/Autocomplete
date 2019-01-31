<<<<<<< HEAD
#include "mainwindow.h"
#include <QApplication>

#include "automata.h"

=======
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include <ctime>
<<<<<<< HEAD
#include <memory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::vector<std::string> words;
=======



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

>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28

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
<<<<<<< HEAD
    Automata automa(words);
=======
    Automata a(words);
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28
    time(&end);

    words.clear();

<<<<<<< HEAD
    automa.setNumOfWords(10);

    std::cout<<"build\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    automa.printInfo();

    std::cout<<"READY"<<std::endl;

    MainWindow w(&automa);
    w.show();

    return a.exec();
=======
    std::cout<<"build\t-\t"<<  difftime (end,begin) <<" s. " <<std::endl;

    a.print();

    std::cout<<"END"<<std::endl;

    std::cin.get();


    return 0;
>>>>>>> 61b3a8b053adac55df9318590b195669ea10db28
}
