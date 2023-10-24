#include "model.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::vector;

model::model(QObject *parent)
    : QObject{parent}
{
    gameOver = false;
}
void model::startButtonClickedSlot()
{
    //This sends the signal to MainWindow to make all buttons disabled
    emit disableStart(true);

    //This will be the random pattern of button flashes
    vector<int> pattern;

    //The first round will have three button flashes
    int patternLength = 3;

    QTimer timer(this);

    //This is where I generate the pattern for the buttons to flash. 0 = blue and 1 = red.
    while (patternLength > 0)
    {
        pattern.push_back(arc4random() % 2);
        patternLength--;
    }

    while (!gameOver)
    {
        for (int i = 0; i < pattern.size(); i++)
        {
            //for every color code in the pattern, we will delay each color flash by a second
            //and emit a flashColor signal with the current color code passed in as a parameter
            //to let MainWindow know that the flash slot needs to be called.
            QTimer::singleShot(i * 1000, this, [=] () {
                emit flashColor(pattern[i]);
            });
        }

        //increases the pattern by one every round
        pattern.push_back(arc4random() % 2);

        //This is just the logic for invoking a game over. For now it will just break out of the
        //loop after the first iteration. In the future, each iteration of the loop will be a new
        //round, and once the player makes a mistake, this if statement will be invoked to send a
        //game over signal and end the game.
        if (true)
        {
            break;
//          gameOver = true;
//          ui->statusLabel->setText("Game Over");
        }
    }
}
