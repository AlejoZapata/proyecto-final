#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene),
    currentSceneIndex(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    images.append(QImage(":/inicio/Inicio.jpg"));
    images.append(QImage(":/escenarios/barco2.jpg"));

    imageFileNames.append(":/Inicio.jpg");
    imageFileNames.append(":/barco2.jpg");

    loadScene(currentSceneIndex);

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadScene(int index)
{
    if (index >= 0 && index < images.size())
    {
        QImage img = images[index];

        scene->clear();

        QPixmap pixmap = QPixmap::fromImage(img);
        pixmap = pixmap.scaled(ui->graphicsView->size(), Qt::KeepAspectRatio);

        scene->addPixmap(pixmap);

        scene->setSceneRect(pixmap.rect());

        qDebug() << "Loaded scene index:" << index;


        ui->pushButton->setVisible(index == 0);
    }
}

void MainWindow::on_pushButton_clicked()
{
    currentSceneIndex = 1;

    qDebug() << "Button clicked, new scene index:" << currentSceneIndex;

    loadScene(currentSceneIndex);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    moving(false)
{
    ui->setupUi(this);

    personaje = new Personaje(this);
    personaje->setPosicion(100, 100); // Posición inicial del personaje

    animTimer = new QTimer(this);
    connect(animTimer, &QTimer::timeout, [this](){
        if (moving) {
            personaje->actualizarAnimacion();
        }
    });
    animTimer->start(100); // Actualizar cada 100 ms
}

MainWindow::~MainWindow() {
    delete ui;
    delete personaje;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    moving = true;
    personaje->mover(event);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    moving = false;
}
