#include "game.h"
#include "enemigo.h"
#include "flecha.h"
#include "antorcha.h"
#include "campo.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include "casa.h"
#include <random>
#include "enemigo2.h"
void Game::setLevelBackground(const QString &imagePath) {
    QPixmap originalImage(imagePath);
    levelBackground = originalImage.scaled(800, 600, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    setBackgroundBrush(levelBackground);
}



Game::Game(QWidget *parent) : QGraphicsView(parent), currentLevel(1), enemiesSpawned(0) {

    scene = new QGraphicsScene(this);
    setScene(scene);


    player = new Personaje();
    player->setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking1/Hit/5.png"));
    scene->addItem(player);
    player->setPos(-150, 100);

    setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);
    setFocusPolicy(Qt::StrongFocus);

    // Iniciar nivel
    startLevel1();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        if (player->x() > 0)
            player->setPos(player->x() - 10, player->y());
    } else if (event->key() == Qt::Key_Right) {
        if (player->x() + player->pixmap().width() < scene->width())
            player->setPos(player->x() + 10, player->y());
    } else if (event->key() == Qt::Key_Up) {
        if (player->y() > 0)
            player->setPos(player->x(), player->y() - 10);
    } else if (event->key() == Qt::Key_Down) {
        if (player->y() + player->pixmap().height() < scene->height())
            player->setPos(player->x(), player->y() + 10);
    } else if (event->key() == Qt::Key_Space) {
        if (currentLevel == 1) {
            player->shootFlecha();
        } else if (currentLevel == 2) {
            player->shootAntorcha();
        }
    } else if (event->key() == Qt::Key_T) {
        player->shootFlecha();
    } else if (event->key() == Qt::Key_U) {
        player->shootAntorcha();
    }
}

void Game::handleFlechaShoot() {
    player->shootFlecha();
}

void Game::handleAntorchaShoot() {
    player->shootAntorcha();
}

void Game::startLevel1() {
    currentLevel = 1;
    setLevelBackground("C:/Users/juana/Downloads/barco2.jpg");


    enemiesSpawned = 0;


    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, [this, enemyTimer]() {
        if (enemiesSpawned < 20) {
            Enemigo *enemy = new Enemigo(true);
            scene->addItem(enemy);
            enemiesSpawned++;
        } else {
            enemyTimer->stop();
        }
    });
    enemyTimer->start(2000);  // Cada 2 segundos aparece un enemigo
}

void Game::startLevel2() {
    currentLevel = 2;
    setLevelBackground("C:/Users/juana/Downloads/zonaverde.png");

    // Generar 10 casas
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, int(scene->width() - 100));
    std::uniform_int_distribution<> disY(50, int(scene->height() / 2));

    for (int i = 0; i < 10; ++i) {
        Casa *casa = new Casa();
        casa->setPos(disX(gen), disY(gen));
        scene->addItem(casa);
    }

    QTimer::singleShot(30000, [this]() {

    });
}

void Game::startLevel3() {
    currentLevel = 3;
    setLevelBackground("C:/Users/juana/Downloads/nivel3.jpg");

    // Crear el campo de fuerza
    Campo *campo = new Campo(player);
    scene->addItem(campo);

    // Generar enemigos Enemigo
    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, [this]() {
        Enemigo *enemy = new Enemigo(false);
        scene->addItem(enemy);
    });
    enemyTimer->start(2000);

    // Generar enemigos Enemigo2
    QTimer *enemy2Timer = new QTimer(this);
    connect(enemy2Timer, &QTimer::timeout, this, &Game::spawnEnemigo2);
    enemy2Timer->start(3000); // Cada 3 segundos aparece un enemigo2

    QTimer::singleShot(30000, [this]() {
        // Finalizar nivel después de 30 segundos
    });
}

void Game::spawnEnemigo2() {
    Enemigo2 *enemy2 = new Enemigo2();
    scene->addItem(enemy2);
}
