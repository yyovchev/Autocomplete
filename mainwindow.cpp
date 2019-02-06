#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(Automata *a, QWidget *parent)
    :   QMainWindow(parent)
    ,   ui(new Ui::MainWindow)
    ,   automata(a)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_prefix_textChanged()
{
    ui->wordsList->clear();
    std::string pref = ui->prefix->text().toStdString();

    std::shared_ptr<Automata::StringList> listPtr = automata->find(pref);

    for (auto word : *listPtr){
       ui->wordsList->appendPlainText(QString::fromStdString(word));
    }
}


void MainWindow::on_numOfWords_valueChanged(int arg1)
{
    this->automata->setNumOfWords(arg1);
}

void MainWindow::on_addBtn_clicked()
{
    std::string newWord = ui->newWord->text().toStdString();
    automata->addWord(newWord);
}
