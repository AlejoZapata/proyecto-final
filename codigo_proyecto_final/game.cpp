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
#include <QMessageBox>
void Game::setLevelBackground(const QString &imagePath) {
    QPixmap originalImage(imagePath);
    levelBackground = originalImage.scaled(800, 600, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    setBackgroundBrush(levelBackground);
}

void Game::showLoadingScreen() {
    QPixmap backgroundImage(":levels/back/load");
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
    setLevelBackground(":levels/back/nivel1");

    QGraphicsTextItem *comicText1 = new QGraphicsTextItem("¿Estaremos cometiendo un error al dirigirnos a Lindisfarne?");
    comicText1->setFont(QFont("Arial", 16, QFont::Bold));
    comicText1->setDefaultTextColor(Qt::black);
    comicText1->setTextWidth(400);
    comicText1->setPos(scene->width() / 2 - comicText1->boundingRect().width() / 2, scene->height() / 4 - comicText1->boundingRect().height());
    scene->addItem(comicText1);

    QTimer::singleShot(5000, [=]() {
        scene->removeItem(comicText1);
        delete comicText1;

        QGraphicsTextItem *comicText2 = new QGraphicsTextItem("¡Oh no! Nos están atacando.\n¡No dejes que pasen! Lánzales hachas con \"T\".");
        comicText2->setFont(QFont("Arial", 16, QFont::Bold));
        comicText2->setDefaultTextColor(Qt::black);
        comicText2->setTextWidth(400);
        comicText2->setPos(scene->width() / 2 - comicText2->boundingRect().width() / 2, scene->height() / 4 - comicText2->boundingRect().height());
        scene->addItem(comicText2);

        QTimer::singleShot(5000, [=]() {
            scene->removeItem(comicText2);
            delete comicText2;

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
        });
    });
}

void Game::startLevel2() {
    currentLevel = 2;
    setLevelBackground(":levels/back/nivel2");

    QGraphicsTextItem *comicText1 = new QGraphicsTextItem("Nos están exigiendo pagar impuestos para comerciar.");
    comicText1->setFont(QFont("Arial", 16, QFont::Bold));
    comicText1->setDefaultTextColor(Qt::black);
    comicText1->setTextWidth(400);
    comicText1->setPos(scene->width() / 2 - comicText1->boundingRect().width() / 2, scene->height() / 4 - comicText1->boundingRect().height());
    scene->addItem(comicText1);

    QTimer::singleShot(5000, [=]() {
        scene->removeItem(comicText1);
        delete comicText1;

        QGraphicsTextItem *comicText2 = new QGraphicsTextItem("¡Destrúyelos! Con \"U\", lanza antorchas.");
        comicText2->setFont(QFont("Arial", 16, QFont::Bold));
        comicText2->setDefaultTextColor(Qt::black);
        comicText2->setTextWidth(400);
        comicText2->setPos(scene->width() / 2 - comicText2->boundingRect().width() / 2, scene->height() / 4 - comicText2->boundingRect().height());
        scene->addItem(comicText2);

        QTimer::singleShot(5000, [=]() {
            scene->removeItem(comicText2);
            delete comicText2;

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
        });
    });
}

void Game::startLevel3() {
    currentLevel = 3;
    enemiesOutOfBounds = 0;

    setLevelBackground(":levels/back/nivel3");

    QGraphicsTextItem *comicText1 = new QGraphicsTextItem("Todos saben que estamos aquí.");
    comicText1->setFont(QFont("Arial", 16, QFont::Bold));
    comicText1->setDefaultTextColor(Qt::red);
    comicText1->setTextWidth(400);
    comicText1->setPos(scene->width() / 2 - comicText1->boundingRect().width() / 2, scene->height() / 4 - comicText1->boundingRect().height());
    scene->addItem(comicText1);

    QTimer::singleShot(5000, [=]() {
        scene->removeItem(comicText1);
        delete comicText1;

        QGraphicsTextItem *comicText2 = new QGraphicsTextItem("¡Sobrevive!");
        comicText2->setFont(QFont("Arial", 30, QFont::Bold));
        comicText2->setDefaultTextColor(Qt::red);
        comicText2->setTextWidth(400);
        comicText2->setPos(scene->width() / 2 - comicText2->boundingRect().width() / 2, scene->height() / 4 - comicText2->boundingRect().height());
        scene->addItem(comicText2);

        QTimer::singleShot(5000, [=]() {
            scene->removeItem(comicText2);
            delete comicText2;

            Campo *campo = new Campo(player);
            scene->addItem(campo);
            connect(campo, &Campo::enemyReachedMidpoint, this, &Game::onEnemyReachedMidpoint);

            QTimer *enemyTimer = new QTimer(this);
            timers.append(enemyTimer);
            connect(enemyTimer, &QTimer::timeout, [this]() {
                Enemigo *enemy = new Enemigo(false);
                scene->addItem(enemy);
                connect(enemy, &Enemigo::enemyOutOfBounds, this, &Game::onEnemyOutOfBounds);
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
        });
    });
}

void Game::spawnEnemigo2() {
    Enemigo2 *enemy2 = new Enemigo2();
    scene->addItem(enemy2);
}
void Game::onEnemyOutOfBounds() {
    qDebug() << "¡Enemigo se salió del mapa!";
    enemiesOutOfBounds++;
    qDebug() << "enemiesOutOfBounds: " << enemiesOutOfBounds;
    if (enemiesOutOfBounds >= 1 && !gameOverDisplayed) {
        qDebug() << "¡Has perdido el nivel!";
        gameOverDisplayed = true;
        clearLevel();
        showGameOverMessage();

    }
}
void Game::onEnemyReachedMidpoint() {
    qDebug() << "¡Enemigo llegó a la mitad del campo!";
    qDebug() << "¡Has perdido el nivel!";
    clearLevel();
    QTimer::singleShot(200, this, &Game::showGameOverMessage);
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
void Game::showGameOverMessage() {
    clearLevel();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Game Over");
    msgBox.setText("¡GAME OVER!\nCerrando el juego");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);

    msgBox.setStyleSheet("QLabel {font-size: 20px;}"
                         "QPushButton {min-width: 100px; font-size: 16px; padding: 5px;}");

    msgBox.exec();
    QApplication::quit();
}
