#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "automata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Automata *a = nullptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_prefix_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Automata *automata;
};

#endif // MAINWINDOW_H
