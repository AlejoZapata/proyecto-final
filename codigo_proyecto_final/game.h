#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "personaje.h"

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void setLevelBackground(const QString &imagePath);
private:
    QGraphicsScene *scene;
    Personaje *player;
    int currentLevel;
    QPixmap levelBackground;
};

#endif // GAME_H
