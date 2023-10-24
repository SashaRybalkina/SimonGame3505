#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Model.h"
#include <QTimer>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::vector;
using std::cout;
using std::endl;

MainWindow::MainWindow(Model& model, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,100,100);}"
                                "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);}"
                                         "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->startButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,215,100);}"
                                          "QPushButton:pressed {background-color: rgb(250,215,150);}"));
    connect(ui->startButton, &QPushButton::clicked, &model, &Model::startButtonClickedSlot);

    connect(&model, &Model::flashColor, this, &MainWindow::flash);
    //              signal recieved     affects this class      uses the flash slot.

    connect(ui->blueButton, &QPushButton::clicked, &model, &Model::blueClicked);

    connect(ui->redButton, &QPushButton::clicked, &model, &Model::redClicked);

    connect(&model, &Model::disableStart, this,
            [this]() {
                ui->startButton->setDisabled(true);
                ui->blueButton->setDisabled(true);
                ui->redButton->setDisabled(true);
    });

    connect(&model, &Model::enableColorButtons, this,
            [this]() {
                ui->blueButton->setDisabled(false);
                ui->redButton->setDisabled(false);
            });

    connect(&model, &Model::gameOverSignal, this,
            [this]() {
                ui->startButton->setDisabled(false);
                ui->blueButton->setDisabled(true);
                ui->redButton->setDisabled(true);
                ui->statusLabel->setText("Game Over");
            });

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
        QTimer::singleShot(1000, this, [=] () {
            ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(200,200,250);}"
                                                  "QPushButton:pressed {background-color: rgb(150,150,255);}"));
        });
        QTimer::singleShot(2000, this, [=] () {
            ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(100,100,250);}"
                                                  "QPushButton:pressed {background-color: rgb(150,150,255);}"));
        });
    }


    else
    {
        //flash red
        QTimer::singleShot(2000, this, [=] () {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,200,200);}"
                                    "QPushButton:pressed {background-color: rgb(255,150,150);}"));
        });
        QTimer::singleShot(2000, this, [=] () {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(250,100,100);}"
                                    "QPushButton:pressed {background-color: rgb(255,150,150);}"));
        });
    }
}

