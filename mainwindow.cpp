#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "model.h"
#include <QTimer>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::vector;
using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,100,100);}"
                                "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);}"
                                         "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->startButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,215,100);}"
                                          "QPushButton:pressed {background-color: rgb(250,215,150);}"));
    connect(ui->startButton, &QPushButton::clicked, this, &model::startButtonClickedSlot);

    connect(&model, &model::flashColor, this, &MainWindow::flash(flashColor));
    //              signal recieved     affects this class      uses the flash slot.

    connect(&model, &model::disableStart, ui->startButton, &QPushButton::setDisabled);
    //              signal recieved       button affected                action, in this case disabling the start button

    connect(&model, &model::disableStart, ui->blueButton, &QPushButton::setDisabled);

    connect(&model, &model::disableStart, ui->redButton, &QPushButton::setDisabled);

    gameOver = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

//This is the slot that is supposed to get called when a signal to flash colors is sent.
void MainWindow::flash(int colorCode)
{
    if (colorCode == 0)
    {
        //flash blue
        ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,200,250);}"
                                    "QPushButton:pressed {background-color: rgb(150,150,255);}"));
        ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);}"
                                    "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    }
    else
    {
        //flash red
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,200,200);}"
                                    "QPushButton:pressed {background-color: rgb(255,150,150);}"));
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,100,100);}"
                                    "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    }
}

