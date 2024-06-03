#ifndef CAMPO_H
#define CAMPO_H

#include <QGraphicsEllipseItem>
#include <QObject>
#include "Personaje.h"
#include <fstream>


using namespace std;

class Campo : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    explicit Campo(Personaje *personaje, QGraphicsItem *parent = nullptr);
    void logEvent(const string &message);
private:
    Personaje *personaje;
    ofstream logFile;
signals:
    void enemyReachedMidpoint();
public slots:
    void affectEnemies();
};

#endif // CAMPO_H
