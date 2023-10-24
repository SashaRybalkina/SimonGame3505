#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);
    bool gameOver;

signals:
    void flashColor(int colorCode);
    void disableStart(bool);
    void gameOverSignal(bool);
    void enableColorButtons(bool);

public slots:
    void startButtonClickedSlot();
    bool blueClicked();
    bool redClicked();

};

#endif // MODEL_H
