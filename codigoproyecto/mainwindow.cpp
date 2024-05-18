#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene),
    currentSceneIndex(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    images.append(QImage("C:/Users/juana/Downloads/_4d4dba4c-a651-4804-ae37-8014e6c73718.jpg"));
    images.append(QImage("C:/Users/juana/Downloads/barco2.jpg"));

    imageFileNames.append("C:/Users/juana/Downloads/_4d4dba4c-a651-4804-ae37-8014e6c73718.jpg");
    imageFileNames.append("C:/Users/juana/Downloads/barco2.jpg");

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
