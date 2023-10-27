#include "Model.h"
#include <QTimer>
#include <vector>
#include <iostream>
using std::vector;

Model::Model(QObject *parent) : QObject{parent} {
    lightSpeed = 1500;
    speedValue = 1;
}

void Model::startButtonClickedSlot(){
    emit disableStart();

    int patternLength = 2;

    pattern.clear();

    while (patternLength > 0)
    {
        pattern.push_back(arc4random() % 2);
        patternLength--;
    }

    nextRound();
}

void Model::nextRound() {
    index = 0;
    current = 0;

    emit updateProgressBar(0);
    pushbackColor();
    speedUp();

    QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    QTimer::singleShot(lightSpeed/speedValue * 1.5, this, &Model::lightOff);
}

void Model::speedUp(){
    if(lightSpeed > 200) {
       lightSpeed -= 200;
    }
}

void Model::pushbackColor(){
    pattern.push_back(arc4random() % 2);
}

void Model::lightOn() {
    if(index < (int)pattern.size()) {
        color = pattern.at(index);
        index++;
        emit flashOn(color);
        QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    }
}

void Model::lightOff() {
    int size = (int)pattern.size();
    if(index < size){
        emit flashOff(color);
        QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOff);
    }

    else if(index == size){
        lastButtonFlash();
    }

}

void Model::lastButtonFlash() {
    emit flashOff(color);
    emit enableColorButtons();
}
void Model::blueClicked() {

    if(pattern.at(current) == 1) {
        current++;
        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }

    else {
        // restart game
    }
}

void Model::redClicked() {

     if(pattern.at(current) == 0) {
        current++;

        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }
    else {
        // restart game
    }
}

void Model::updateProgress(double i) {
    double progress = i / (double) pattern.size() * 100;
    emit updateProgressBar(progress);
    emit updatePercentage(progress);
}


void Model::gameOver(){
    emit updateProgressBar(0);
    pattern.clear();
}

void Model::setSpeedValue(double value)
{
    speedValue = 1 + value/2;
}

