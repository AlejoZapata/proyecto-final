#include "game.h"
#include "enemigo.h"
#include "flecha.h"
#include "antorcha.h"
#include "campo.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>

void Game::setLevelBackground(const QString &imagePath) {
    QPixmap originalImage(imagePath);

    // Escalar la imagen para que se ajuste al tamaño de la ventana del juego
    levelBackground = originalImage.scaled(800, 600, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    setBackgroundBrush(levelBackground);
}

Game::Game(QWidget *parent) : QGraphicsView(parent), currentLevel(1), enemiesSpawned(0) {
    // Crear la escena
    scene = new QGraphicsScene(this);
    setScene(scene);

    // Crear el personaje principal
    player = new Personaje();
    player->setPixmap(QPixmap("C:/Users/juana/Downloads/Vikings/Viking1/Hit/5.png"));
    scene->addItem(player);
    player->setPos(-150, 100);  // Posición inicial del personaje

    // Configurar la vista
    setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);

    // Permitir que la vista procese eventos de teclado
    setFocusPolicy(Qt::StrongFocus);

    // Iniciar el primer nivel
    startLevel1();
}

void Game::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Left) {
        if (player->x() > 0)
            player->setPos(player->x() - 10, player->y());
    } else if (event->key() == Qt::Key_Right) {
        if (player->x() + player->pixmap().width() < scene->width())
            player->setPos(player->x() + 10, player->y());
    } else if (event->key() == Qt::Key_Space) {
        if (currentLevel == 1) {
            player->shootFlecha();
        } else if (currentLevel == 2) {
            player->shootAntorcha();
        }
    } else if (event->key() == Qt::Key_T) {
        player->shootFlecha();
    }
}

void Game::startLevel1() {
    currentLevel = 1;
    setLevelBackground("C:/Users/juana/Downloads/barco2.jpg");

    // Reiniciar el contador de enemigos
    enemiesSpawned = 0;

    // Generar enemigos
    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, [this, enemyTimer]() {
        if (enemiesSpawned < 20) {
            Enemigo *enemy = new Enemigo();
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
    setLevelBackground("C:/Users/juana/Downloads/nivel2.jpg");
    // Establecer un temporizador para el nivel
    QTimer::singleShot(30000, [this]() {  // Nivel de 30 segundos

    });
}

void Game::startLevel3() {
    currentLevel = 3;
    setLevelBackground("C:/Users/juana/Downloads/nivel3.jpg");
    // Crear el campo de fuerza
    Campo *campo = new Campo(player);
    scene->addItem(campo);

    // Generar enemigos
    QTimer *enemyTimer = new QTimer(this);
    connect(enemyTimer, &QTimer::timeout, [this]() {
        Enemigo *enemy = new Enemigo();
        scene->addItem(enemy);
    });
    enemyTimer->start(2000);  // Cada 2 segundos aparece un enemigo

    // Establecer un temporizador para el nivel
    QTimer::singleShot(30000, [this]() {  // Nivel de 30 segundos

    });
}
