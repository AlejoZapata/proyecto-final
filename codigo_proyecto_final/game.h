#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QVector>
#include "personaje.h"
#include "antorcha.h"

class Game : public QGraphicsView {
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void startLevel1();
    void startLevel2();
    void startLevel3();
    void setLevelBackground(const QString &imagePath);
    void showLoadingScreen();
    void clearLevel();
    void showWinMessage();
public slots:
    void handleFlechaShoot();
    void handleAntorchaShoot();
    void spawnEnemigo2();
    void onEnemyOutOfBounds();
    void onEnemyReachedMidpoint();
    void checkWinConditionLevel1();
    void startNextLevel();

private:
    QGraphicsScene *scene;
    Personaje *player;
    int currentLevel;
    QPixmap levelBackground;
    int enemiesSpawned;
    int enemiesOutOfBounds;
    QVector<QTimer*> timers;
};

#endif // GAME_H
