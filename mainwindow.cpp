#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <vector>
using std::vector;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,100,100);}"
                                "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);}"
                                         "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->startButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,215,100);}"
                                          "QPushButton:pressed {background-color: rgb(250,215,150);}"));
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startButtonClickedSlot);

//    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::checkInputBlue);

//    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::checkInputRed);

    gameOver = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startButtonClickedSlot()
{
    vector<button> pattern;
    int patternLength = 3;
    QTimer timer(this);
    while (patternLength > 0)
    {
        if (rand() < 0.5)
        {
            pattern.push_back(button.blue);
        }
        else
        {
            pattern.push_back(button.red);
        }
        patternLength--;
    }

    while (!gameOver)
    {
        for (button color : pattern)
        {
            if (color == button.blue)
            {
                //light up blue
                timer.start(1000);
                ui->blueButton->animateClick();
            }
            else
            {
                //light up red
                timer.start(1000);
                ui->redButton->animateClick();
            }
        }

        pattern.push_back(rand() % 1 + 1);

        if (true)
        {
            gameOver = true;
            ui->statusLabel->setText("Game Over");
        }
    }

//    void checkInputBlue()
//    {

//    }

//    void checkInputRed()
//    {

//    }
}

