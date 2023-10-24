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

    connect(&model, &model::flashColor, this);
    connect(&model, &model::disableStart, ui->startButton, &QPushButton::setDisabled);

    gameOver = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::flash(int colorCode)
{

}

