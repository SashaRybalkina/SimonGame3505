#include "Model.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <vector>
#include <iostream>
#include <stdlib.h>
using std::vector;

Model::Model(QObject *parent)
    : QObject{parent}
{
    gameOver = false;
}
void Model::startButtonClickedSlot()
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

        emit enableColorButtons(true);

        int patternLength2 = pattern.size();
        int index = 0;
        while (patternLength2 > 0)
        {
            if (blueClicked() || redClicked())
            {
                if ((blueClicked() && pattern[index] != 0) || (redClicked() && pattern[index] != 1))
                {
                    emit gameOverSignal(true);
                    gameOver = true;
                    break;
                }
                index++;
                patternLength2--;
            }
        }

        //increases the pattern by one every round
        pattern.push_back(arc4random() % 2);
    }
}

bool blueClicked()
{
    return true;
}

bool redClicked()
{
    return true;
}
