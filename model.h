#ifndef MODEL_H
#define MODEL_H

#include <QObject>

class model : public QObject
{
    Q_OBJECT
public:
    explicit model(QObject *parent = nullptr);
    bool gameOver;

signals:
    void flashColor(int colorCode);
    void disableStart(bool);

public slots:
    void startButtonClickedSlot();

};

#endif // MODEL_H
