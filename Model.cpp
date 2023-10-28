/**
 * Model for Simon Game
 * @author Sasha Rybalkina
 * @author Yeon Kim
 * @date October 27, 2023
 */

#include "Model.h"
#include <QTimer>
#include <vector>
#include <iostream>
using std::vector;

/**
 * @brief Model::Model Constructor
 * @param parent Parent object
 */
Model::Model(QObject *parent) : QObject{parent} {
    lightSpeed = 1500;
    speedValue = 1;
}

/**
 * @brief Model::startButtonClickedSlot When start button is clicked
 */
void Model::startButtonClickedSlot(){
    emit disableStart();

    int patternLength = 2;

    pattern.clear();

    // Randomly generates pattern(red/blue)
    while (patternLength > 0)
    {
        pattern.push_back(arc4random() % 2);
        patternLength--;
    }

    nextRound();
}

/**
 * @brief Model::nextRound Prepare game for next round
 */
void Model::nextRound() {
    index = 0;
    current = 0;

    emit updateProgressBar(0);

    // Add one more color and speed up
    pushbackColor();
    speedUp();

    QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    QTimer::singleShot(lightSpeed/speedValue * 1.5, this, &Model::lightOff);
}

/**
 * @brief Model::speedUp Speeds of the game every round
 */
void Model::speedUp(){
    if(lightSpeed > 200) {
       lightSpeed -= 200;
    }
}

/**
 * @brief Model::pushbackColor Adds one more color
 */
void Model::pushbackColor(){
    pattern.push_back(arc4random() % 2);
}

/**
 * @brief Model::lightOn Light on color
 */
void Model::lightOn() {
    if(index < (int)pattern.size()) {
        color = pattern.at(index);
        index++;
        emit flashOn(color);
        QTimer::singleShot(lightSpeed/speedValue, this, &Model::lightOn);
    }
}

/**
 * @brief Model::lightOff Light off color
 */
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

/**
 * @brief Model::lastButtonFlash When last button flashes, enables color buttons
 */
void Model::lastButtonFlash() {
    emit flashOff(color);
    emit enableColorButtons();
}

/**
 * @brief Model::blueClicked Check if user guessed right when clicked blue
 */
void Model::blueClicked() {

    if(pattern.at(current) == 1) {
        current++;
        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }

    else {
        gameOver();
    }
}

/**
 * @brief Model::redClicked Check if user guessed right when clicked red
 */
void Model::redClicked() {

     if(pattern.at(current) == 0) {
        current++;

        updateProgress((double)current);

        if(current == (int)pattern.size()) {
            QTimer::singleShot(1000, this, &Model::nextRound);
        }
    }
    else {
        gameOver();
    }
}

/**
 * @brief Model::updateProgress Updates progress bar
 * @param i current index
 */
void Model::updateProgress(double i) {
    double progress = i / (double) pattern.size() * 100;
    emit updateProgressBar(progress);
    emit updatePercentage(progress);
}


/**
 * @brief Model::gameOver Updates progress bar and clears pattern list when game over
 */
void Model::gameOver(){
    emit updateProgressBar(0);
    pattern.clear();

    emit gameOverSign();
}

/**
 * @brief Model::setSpeedValue Adjust the speed value
 * @param value speed
 */
void Model::setSpeedValue(double value)
{
    speedValue = 1 + value / 2;
}
