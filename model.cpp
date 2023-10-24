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
    emit disableStart(true);
    vector<int> pattern;
    int patternLength = 3;
    QTimer timer(this);
    while (patternLength > 0)
    {
        pattern.push_back(arc4random() % 2);
        patternLength--;
    }

    while (!gameOver)
    {
        for (int i = 0; i < pattern.size(); i++)
        {
            QTimer::singleShot(i * 1000, this, [=] () {
                emit flashColor(pattern[i]);
            });
//            if (pattern[i] == 0)
//            {
//                //light up blue
//                ui->blueButton->animateClick();
//            }
//            else
//            {
//                //light up red
//                ui->redButton->animateClick();
//            }
        }

        pattern.push_back(arc4random() % 2);

        if (true)
        {
            break;
//          gameOver = true;
//          ui->statusLabel->setText("Game Over");
        }
    }
}
