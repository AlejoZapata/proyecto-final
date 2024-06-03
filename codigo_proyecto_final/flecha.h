#ifndef FLECHA_H
#define FLECHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <fstream>


using namespace std;

class Flecha : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Flecha(bool directionRight, QGraphicsItem *parent = nullptr);
    void logEvent(const string &message);
public slots:
    void move();
private:
    bool directionRight;
    ofstream logFile;
    qreal angle;
};

#endif // FLECHA_H
