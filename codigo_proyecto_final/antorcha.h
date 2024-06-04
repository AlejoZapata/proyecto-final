#ifndef ANTORCHA_H
#define ANTORCHA_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <fstream>

using namespace std;

class Antorcha : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Antorcha(QGraphicsItem *parent = nullptr);
    void setInitialVelocity(float vx, float vy);
    void setInitialVelocityWithAngle(float velIn, float theta);
    void logEvent(const string &message);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
public slots:
    void move();
private:
    float vx, vy;
    float t;
    float g;
    ofstream logFile;
};

#endif // ANTORCHA_H
