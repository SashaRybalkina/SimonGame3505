#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Model.h"

MainWindow::MainWindow(Model& model, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Set button colors
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(250,100,100);}"
                                         "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,250);}"
                                         "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    ui->startButton->setStyleSheet(QString("QPushButton {background-color: rgb(250,215,100);}"
                                          "QPushButton:pressed {background-color: rgb(250,215,150);}"));

    // Connect the buttons with the functions
    connect(ui -> startButton, &QPushButton::clicked, &model, &Model::startButtonClickedSlot);
    connect(ui -> blueButton, &QPushButton::clicked, &model, &Model::blueClicked);
    connect(ui -> redButton, &QPushButton::clicked, &model,&Model::redClicked);

    // Disable blue and red buttons by default
    ui -> blueButton -> setEnabled(false);
    ui -> redButton -> setEnabled(false);

    // Used lambda expresssions for controlling buttons
    connect(&model, &Model::enableStartButton, this,
            [this]() {
                ui -> startButton -> setEnabled(true);
            });

    connect(&model, &Model::enableColorButtons, this,
            [this]() {
                ui -> blueButton -> setEnabled(true);
                ui -> redButton -> setEnabled(true);

            });

    connect(&model, &Model::disableStart, this,
            [this]() {
                ui -> startButton -> setEnabled(false);
                ui -> blueButton -> setEnabled(false);
                ui -> redButton -> setEnabled(false);
            });

//    Game over
//    connect(&model, &Model::gameOverSignal, this,
//            [this]() {
//                ui->startButton->setDisabled(false);
//                ui->blueButton->setDisabled(true);
//                ui->redButton->setDisabled(true);
//                ui->statusLabel->setText("Game Over");
//            });

    connect(&model, &Model::flashOn, this, &MainWindow::flashColorOn);
    connect(&model, &Model::flashOff, this, &MainWindow::flashColorOff);

    connect(&model, &Model::updateProgressBar, ui->progressBar, &QProgressBar::setValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::flashColorOn(int colorCode) {
    // Red
    if(colorCode == 0) {
        ui -> redButton -> setStyleSheet(QString("QPushButton {background-color: rgb(255,150,150);}"
                                                 "QPushButton:pressed {background-color: rgb(250,100,100);}"));
    }
    // Blue
    else {
        ui -> blueButton -> setStyleSheet(QString("QPushButton {background-color: rgb(150,150,225);}"
                                                  "QPushButton:pressed {background-color: rgb(100,100,250);}"));
    }
}


void MainWindow::flashColorOff(int colorCode) {
    // Red
    if(colorCode == 0) {
        ui -> redButton -> setStyleSheet(QString("QPushButton {background-color: rgb(250,100,100);}"
                                             "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    }
    // Blue
    else {
        ui -> blueButton -> setStyleSheet(QString("QPushButton {background-color: rgb(100,100,250);}"
                                                  "QPushButton:pressed {background-color: rgb(150,150,255);}"));
    }

}
