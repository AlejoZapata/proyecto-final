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
#include <QApplication>
#include <QPushButton>
#include <QGraphicsProxyWidget>

void Game::setLevelBackground(const QString &imagePath) {
    QPixmap originalImage(imagePath);
    levelBackground = originalImage.scaled(800, 600, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    setBackgroundBrush(levelBackground);
}
void Game::showLoadingScreen() {

    QPixmap backgroundImage("C:/Users/juana/Downloads/_4d4dba4c-a651-4804-ae37-8014e6c73718 (1).jpg");
    QGraphicsPixmapItem *background = new QGraphicsPixmapItem(backgroundImage.scaled(800, 600));
    scene->addItem(background);


    QPushButton *startButton = new QPushButton("Click para empezar");
    startButton->setFixedSize(300, 60);
    startButton->setFont(QFont("Times New Roman", 20, QFont::Bold));
    QGraphicsProxyWidget *proxy = scene->addWidget(startButton);
    proxy->setPos(scene->width() / 2 - startButton->width() / 2, scene->height() / 2 + 150);


    connect(startButton, &QPushButton::clicked, this, &Game::startLevel1);
    connect(startButton, &QPushButton::clicked, [=]() {
        scene->removeItem(background);
        delete background;
        proxy->setWidget(nullptr);
        delete startButton;
    });
}

Game::Game(QWidget *parent) : QGraphicsView(parent), currentLevel(1), enemiesSpawned(0), enemiesOutOfBounds(0) {
    scene = new QGraphicsScene(this);
    setScene(scene);

    player = new Personaje();
    scene->addItem(player);
    player->setPos(-150, 100);
    setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);
    setFocusPolicy(Qt::StrongFocus);


    showLoadingScreen();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        if (player->x() > 0) {
            player->setPos(player->x() - 10, player->y());
            player->setPixmap(player->sprites[player->spriteIndex]);
            player->spriteIndex = (player->spriteIndex + 1) % 5;
        }
    } else if (event->key() == Qt::Key_Right) {
        if (player->x() + player->pixmap().width() < scene->width()) {
            player->setPos(player->x() + 10, player->y());
            player->setPixmap(player->sprites[player->spriteIndex + 5]);
            player->spriteIndex = (player->spriteIndex + 1) % 5;
        }
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
    enemiesOutOfBounds = 0;

    QTimer *enemyTimer = new QTimer(this);
    timers.append(enemyTimer);
    connect(enemyTimer, &QTimer::timeout, [this, enemyTimer]() {
        if (enemiesSpawned < 20) {
            Enemigo *enemy = new Enemigo(true);
            scene->addItem(enemy);
            connect(enemy, &Enemigo::enemyOutOfBounds, this, &Game::onEnemyOutOfBounds);
            enemiesSpawned++;
        } else {
            enemyTimer->stop();
            checkWinConditionLevel1();
        }
    });
    enemyTimer->start(1900);
}


void Game::startLevel2() {
    currentLevel = 2;
    setLevelBackground("C:/Users/juana/Downloads/zonaverde.png");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disX(0, int(scene->width() - 100));
    std::uniform_int_distribution<> disY(50, int(scene->height() / 2));

    for (int i = 0; i < 10; ++i) {
        Casa *casa = new Casa();
        casa->setPos(disX(gen), disY(gen));
        scene->addItem(casa);
    }

    QTimer *singleShotTimer = new QTimer(this);
    timers.append(singleShotTimer);
    singleShotTimer->singleShot(30000, [this]() {
        startLevel3();
    });
}

void Game::startLevel3() {
    currentLevel = 3;
    setLevelBackground("C:/Users/juana/Downloads/nivel3.jpg");

    Campo *campo = new Campo(player);
    scene->addItem(campo);
    connect(campo, &Campo::enemyReachedMidpoint, this, &Game::onEnemyReachedMidpoint);

    QTimer *enemyTimer = new QTimer(this);
    timers.append(enemyTimer);
    connect(enemyTimer, &QTimer::timeout, [this]() {
        Enemigo *enemy = new Enemigo(false);
        scene->addItem(enemy);
    });
    enemyTimer->start(2000);

    QTimer *enemy2Timer = new QTimer(this);
    timers.append(enemy2Timer);
    connect(enemy2Timer, &QTimer::timeout, this, &Game::spawnEnemigo2);
    enemy2Timer->start(3000);

    QTimer *singleShotTimer = new QTimer(this);
    timers.append(singleShotTimer);
    singleShotTimer->singleShot(10000, [this]() {
        showWinMessage();
    });
}
void Game::spawnEnemigo2() {
    Enemigo2 *enemy2 = new Enemigo2();
    scene->addItem(enemy2);
}

void Game::onEnemyOutOfBounds() {
    qDebug() << "¡Enemigo se salió del mapa!";
    enemiesOutOfBounds++;
    if (enemiesOutOfBounds >= 1) {
        qDebug() << "¡Has perdido el nivel 1!";
        clearLevel();
        startLevel1();
    }
}

void Game::onEnemyReachedMidpoint() {
    qDebug() << "¡Enemigo llegó a la mitad del campo!";
    if (currentLevel == 3) {
        qDebug() << "¡Has perdido el nivel 3!";
        clearLevel();
        startLevel3();
    }
}

void Game::checkWinConditionLevel1() {
    if (enemiesSpawned >= 20 && enemiesOutOfBounds == 0) {
        qDebug() << "¡Has ganado el nivel 1!";
        clearLevel();
        startLevel2();
    }
}

void Game::clearLevel() {
    for (auto item : scene->items()) {
        if (item != player) {
            scene->removeItem(item);
            delete item;
        }
    }

    for (QTimer* timer : timers) {
        timer->stop();
        delete timer;
    }
    timers.clear();
}

void Game::startNextLevel() {
    if (currentLevel == 1) {
        startLevel2();
    } else if (currentLevel == 2) {
        startLevel3();
    }
}

void Game::showWinMessage() {
    clearLevel();
    QGraphicsTextItem *winText = new QGraphicsTextItem("¡Has ganado el juego!");

    QFont font("Times New Roman", 48, QFont::Bold);
    winText->setFont(font);
    winText->setDefaultTextColor(Qt::red);
    winText->setPos(scene->width() / 2 - winText->boundingRect().width() / 2,
                    scene->height() / 2 - winText->boundingRect().height() / 2);

    scene->addItem(winText);

    QTimer::singleShot(5000, []() {
        QApplication::quit();
    });
}
