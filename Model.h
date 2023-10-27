#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <vector>
#include <iostream>
using std::vector;

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = nullptr);


private:
    vector<int> pattern;
    int index;
    int color;
    int current;
    int lightSpeed;
    double speedValue;

public slots:
    void startButtonClickedSlot();
    void pushbackColor();
    void nextRound();
    void speedUp();
    void updateProgress(double i);
    void gameOver();
    void setSpeedValue(double value);

    void lightOn();
    void lightOff();
    void lastButtonFlash();

    void redClicked();
    void blueClicked();


signals:
    void enableColorButtons();
    void enableStartButton();
    void disableStart();

    void gameOverSign();

    void updateProgressBar(int percentage);
    void updatePercentage(int percentage);

    void flashOn(int colorCode);
    void flashOff(int colorCode);
};

#endif // MODEL_H
