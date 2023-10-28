/**
 * Main setup
 * @author Sasha Rybalkina
 * @author Yeon Kim
 * @date October 27, 2023
 */

#include "mainwindow.h"
#include <QApplication>
#include "Model.h"

/**
 * @brief main Starting point of Simon Game
 * @param argc Number of command-line arguments
 * @param argv Char array of command-line arguments
 * @return exit status
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow w(model);
    w.show();
    return a.exec();
}
